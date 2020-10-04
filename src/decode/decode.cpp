/*! \file decode.cpp
 * \brief Decode class implementation.
 *
 * \authors Dmitrii Leliuhin
 * \date July 2020
 */

//=======================================================================================

#include "decode.h"

#include "vbyte_buffer_view.h"
#include "vbyte_buffer.h"
#include "vtime_point.h"
#include "vlog.h"

#include "livox_def.h"

//=======================================================================================

static constexpr float mm = 1000.F;
static constexpr uint8_t delta_ns = 10;

const std::map<uint8_t, uint8_t> point_cloud_size =
{
    { kCartesian,           100 },
    { kSpherical,           100 },
    { kExtendCartesian,     96 },
    { kExtendSpherical,     96 },
    { kDualExtendCartesian, 48 },
    { kDualExtendSpherical, 48 },
    { kImu,                 1 },
};

//=======================================================================================
Decode::Decode( const Config& conf )
    : _conf ( conf                )
{
    _pack.clear();

    _pos( _conf.receive.pos );
    _lvx( _conf.receive.lvx );
}
//=======================================================================================


#include <QByteArray>
#include <QIODevice>
#include <QFile>
//=======================================================================================
void Decode::_pos( const std::string& path )
{
    QFile file( path.c_str() );
    file.open( QIODevice::OpenModeFlag::ReadOnly );

    auto data = file.readAll();
    file.close();

    vbyte_buffer buf( data.data() );
    auto rows = buf.split_by_spaces();

    for ( auto i = 0; i < rows.size(); ++i )
    {
        auto vals = rows.at(i).split(',');

        if ( vals.size() != 9 )
            continue;

        PosData tmp;
        {
            tmp.timestamp = vals.at(0).to_double();
            tmp.longitude = vals.at(1).to_double();
            tmp.latitude  = vals.at(2).to_double();
            tmp.height    = vals.at(3).to_double();
            tmp.roll      = vals.at(4).to_double();
            tmp.pitch     = vals.at(5).to_double();
            tmp.yaw       = vals.at(6).to_double();
            tmp.easting   = vals.at(7).to_double();
            tmp.northing  = vals.at(8).to_double();
        }

        _pack.pos.emplace( static_cast<uint32_t>( tmp.timestamp * 1000 ), tmp );
    }
}
//=======================================================================================


//=======================================================================================
LivoxRawPoint decode_raw_pnt( vbyte_buffer_view* view )
{
    LivoxRawPoint res;

    res.x            = view->i32_LE();
    res.y            = view->i32_LE();
    res.z            = view->i32_LE();
    res.reflectivity = view->u8();

    return res;
}
//=======================================================================================
LivoxSpherPoint decode_spher_pnt( vbyte_buffer_view* view )
{
    LivoxSpherPoint res;

    res.depth        = view->u32_LE();
    res.theta        = view->u16_LE();
    res.phi          = view->u16_LE();
    res.reflectivity = view->u8();

    return res;
}
//=======================================================================================
LivoxExtendRawPoint decode_ext_raw_pnt( vbyte_buffer_view* view )
{
    LivoxExtendRawPoint res;

    res.x            = view->i32_LE();
    res.y            = view->i32_LE();
    res.z            = view->i32_LE();
    res.reflectivity = view->u8();
    res.tag          = view->u8();

    return res;
}
//=======================================================================================
LivoxExtendSpherPoint decode_ext_spher_pnt( vbyte_buffer_view* view )
{
    LivoxExtendSpherPoint res;

    res.depth        = view->u32_LE();
    res.theta        = view->u16_LE();
    res.phi          = view->u16_LE();
    res.reflectivity = view->u8();
    res.tag          = view->u8();

    return res;
}
//=======================================================================================
LivoxDualExtendRawPoint decode_dual_ext_raw_pnt( vbyte_buffer_view* view )
{
    LivoxDualExtendRawPoint res;

    res.x1            = view->i32_LE();
    res.y1            = view->i32_LE();
    res.z1            = view->i32_LE();
    res.reflectivity1 = view->u8();
    res.tag1          = view->u8();
    res.x2            = view->i32_LE();
    res.y2            = view->i32_LE();
    res.z2            = view->i32_LE();
    res.reflectivity2 = view->u8();
    res.tag2          = view->u8();

    return res;
}
//=======================================================================================
LivoxDualExtendSpherPoint decode_dual_ext_spher_pnt( vbyte_buffer_view* view )
{
    LivoxDualExtendSpherPoint res;

    res.theta         = view->u16_LE();
    res.phi           = view->u16_LE();
    res.depth1        = view->u32_LE();
    res.reflectivity1 = view->u8();
    res.tag1          = view->u8();
    res.depth2        = view->u32_LE();
    res.reflectivity2 = view->u8();
    res.tag2          = view->u8();

    return res;
}
//=======================================================================================

#include <QtMath>

//=======================================================================================
template <typename T>
T to_cartesian( const float theta, const float phi, const float depth )
{
    T res;

    res.x = float( depth * qSin( theta ) * qCos( phi ) ) / mm;
    res.y = float( depth * qSin( theta ) * qSin( phi ) ) / mm;
    res.z = float( depth * qCos( theta ) ) / mm;

    return res;
}
//=======================================================================================
template <typename TI, typename TO>
TO to_cartesian( const TI& pnt )
{
    auto theta_rad = qDegreesToRadians( qreal( pnt.theta / 100. ) );
    auto phi_rad   = qDegreesToRadians( qreal( pnt.phi / 100. ) );

    return to_cartesian<TO>( theta_rad, phi_rad, pnt.depth );
}
//=======================================================================================
template <typename T>
T mm_to_meters( const int32_t x, const int32_t y, const int32_t z )
{
    T res;

    res.x = x / mm;
    res.y = y / mm;
    res.z = z / mm;

    return res;
}
//=======================================================================================



//=======================================================================================
void Decode::_lvx( const std::string& path )
{
    QFile file( path.c_str() );
    file.open( QIODevice::OpenModeFlag::ReadOnly );

    auto data = file.readAll();

    file.close();

    vbyte_buffer_view view( data.data(), uint( data.size() ) );

    auto buf = view.show_tail();

    if ( !buf.starts_with( livox_tech ) )
        throw verror << "Lvx file is broken";

    // Public Header Block

    LvxFilePublicHeader public_header;
    {
        for ( auto i = 0; i < 16; ++i )
            public_header.signature[i] = view.u8();

        for ( auto i = 0; i < 4; ++i )
            public_header.version[i] = view.u8();

        public_header.magic_code = view.u32_LE();
    }

    if ( public_header.magic_code != magic_code )
        throw verror << "Bad magic number";

    // Private Header Block

    LvxFilePrivateHeader private_header;
    {
        private_header.frame_duration = view.u32_LE();
        private_header.device_count = view.u8();
    }

    // Devices Info Block

    for ( auto i = 0; i < private_header.device_count; ++i )
    {
        LvxDeviceInfo info;
        {
            for ( auto j = 0; j < 16; ++j )
                info.lidar_broadcast_code[j] = view.u8();

            for ( auto j = 0; j < 16; ++j )
                info.hub_broadcast_code[j] = view.u8();

            info.device_index = view.u8();
            info.device_type = view.u8();
            info.extrinsic_enable = view.u8();
            info.roll = view.float_LE();
            info.pitch = view.float_LE();
            info.yaw = view.float_LE();
            info.x = view.float_LE();
            info.y = view.float_LE();
            info.z = view.float_LE();
        }
    }

    // Point Cloud Data Block

    FrameHeader frame_header;
    {
        frame_header.current_offset = view.u64_LE();
        frame_header.next_offset    = view.u64_LE();
        frame_header.frame_index    = view.u64_LE();
    }

    LvxBasePackDetail prev_package;
    LidarSetUtcSyncTimeRequest prev_ts;

    while ( view.remained() > 0 )
    {
        LvxBasePackDetail package;
        {
            package.device_index = view.u8();
            package.version = view.u8();
            package.port_id = view.u8();
            package.lidar_index = view.u8();
            package.rsvd = view.u8();
            package.error_code = view.u32_LE();
            package.timestamp_type = view.u8();
            package.data_type = view.u8();

            for ( auto i = 0; i < 8; ++i )
                package.timestamp[i] = 0;

            LidarSetUtcSyncTimeRequest ts;
            ts.year = view.u8();
            ts.month = view.u8();
            ts.day = view.u8();
            ts.hour = view.u8();
            ts.mircrosecond = view.u32_LE();

            if ( ( ts.year < 19 ) || ( ts.year > vtime_point::now().humanable().year() - 1999 ) ||
                 ( ts.month <= 0 ) || ( ts.month > 12 ) ||
                 ( ts.day <= 0 ) || ( ts.day > 31 ) ||
                 ( ts.hour < 0 ) || ( ts.hour > 24 ) )
            {
//                vdeb << +ts.year << +ts.month << +ts.day << +ts.hour << ts.mircrosecond;

                view.omit( point_cloud_size.find( package.data_type )->second * sizeof ( LivoxSpherPoint ) );
                continue;
            }

            prev_package = package;
            prev_ts = ts;

            auto year = vcat::from_text<int>( "20" + std::to_string( ts.year ) );

            auto full_ts = vtime_point::from_utc( year,
                                                  ts.month,
                                                  ts.day,
                                                  ts.hour, 0, 0 ).nanoseconds().count() + ts.mircrosecond * 1000;

            auto cur_day = _weekday( ts.day, ts.month, year );

            if ( ts.day <= cur_day )
            {
                view.omit( point_cloud_size.find( package.data_type )->second * sizeof ( LivoxSpherPoint ) );
                continue;
            }

            auto rem_ts = vtime_point::from_utc( year,
                                                 ts.month,
                                                 ts.day - cur_day,
                                                 0, 0, 0 ).nanoseconds().count();

            auto week_ns = full_ts - rem_ts;

            auto last_ns = week_ns;

            for ( auto i = 0; i < uint( point_cloud_size.find( package.data_type )->second ); ++i )
            {
                LivoxPoint tmp;

                if ( package.data_type == kCartesian )
                {
                    auto pnt = decode_raw_pnt( &view );

                    tmp = mm_to_meters<LivoxPoint>( pnt.x, pnt.y, pnt.z );
                    tmp.reflectivity = pnt.reflectivity;
                }

                else if ( package.data_type == kSpherical )
                {
                    auto pnt = decode_spher_pnt( &view );

                    tmp = to_cartesian<LivoxSpherPoint, LivoxPoint>( pnt );
                    tmp.reflectivity = pnt.reflectivity;
                }

                else if ( package.data_type == kExtendCartesian )
                {
                    auto pnt = decode_ext_raw_pnt( &view );

                    tmp = mm_to_meters<LivoxPoint>( pnt.x, pnt.y, pnt.z );
                    tmp.reflectivity = pnt.reflectivity;
                }

                else if ( package.data_type == kExtendSpherical )
                {
                    auto pnt = decode_ext_spher_pnt( &view );

                    tmp = to_cartesian<LivoxExtendSpherPoint, LivoxPoint>( pnt );
                    tmp.reflectivity = pnt.reflectivity;
                }

                else if ( package.data_type == kDualExtendCartesian )
                {
                    auto pnt = decode_dual_ext_raw_pnt( &view );
                }

                else if ( package.data_type == kDualExtendSpherical )
                {
                    auto pnt = decode_dual_ext_spher_pnt( &view );
                }

                else if ( package.data_type == kImu )
                {}

                else if ( package.data_type == kMaxPointDataType )
                {}

                _test.emplace( last_ns, ts );
                _pack.lvx.emplace( last_ns, tmp );

                last_ns += delta_ns;
            }
        }
    }
}
//=======================================================================================
int Decode::_weekday( const int& d, const int& m, int y )
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

    y -= m < 3;

    return ( y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}
//=======================================================================================
