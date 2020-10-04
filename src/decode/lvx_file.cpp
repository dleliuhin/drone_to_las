#include <time.h>
#include <cmath>
#include "lvx_file.h"

//=======================================================================================

static constexpr auto write_buf_len  = 1024 * 1024;
static constexpr auto raw_pnt_num    = 100;
static constexpr auto single_pnt_num = 96;
static constexpr auto dual_pnt_num   = 48;
static constexpr auto imu_pnt_num    = 1;

//=======================================================================================


//=======================================================================================
LvxFile::LvxFile()
    : _cur_frame_index ( 0                         )
    , _frame_duration  ( kDefaultFrameDurationTime )
    , _cur_offset      ( 0                         )
{

}
//=======================================================================================


//=======================================================================================
bool LvxFile::open( const QString& path )
{
    time_t curtime = time( nullptr );
    char filename[30] = {0};

    tm* local_time = localtime( &curtime );

    auto fname = "%Y-%m-%d_%H-%M-%S.lvx";
    strftime( filename, sizeof( filename ), fname, local_time );

    QString tmp = path;
    tmp.append( filename );

    _file.open( tmp.toStdString(), std::ios::out | std::ios::binary );

    if ( !_file.is_open() )
        return false;

    return true;
}
//=======================================================================================
void LvxFile::init_header()
{
    LvxFilePublicHeader lvx_file_public_header {0};
    std::unique_ptr<char[]> write_buffer( new char[ write_buf_len ] );
    std::string signature = "livox_tech";
    memcpy( lvx_file_public_header.signature, signature.c_str(), signature.size() );

    lvx_file_public_header.version[0] = 1;
    lvx_file_public_header.version[1] = 1;
    lvx_file_public_header.version[2] = 0;
    lvx_file_public_header.version[3] = 0;

    lvx_file_public_header.magic_code = magic_code;

    memcpy( write_buffer.get() + _cur_offset,
            static_cast<void *>( &lvx_file_public_header ),
            sizeof( LvxFilePublicHeader ) );
    _cur_offset += sizeof( LvxFilePublicHeader );

    auto device_count = static_cast<uint8_t>( _device_info_list.size() );
    LvxFilePrivateHeader lvx_file_private_header {0};
    lvx_file_private_header.frame_duration = _frame_duration;
    lvx_file_private_header.device_count = device_count;

    memcpy( write_buffer.get() + _cur_offset,
            static_cast<void *>( &lvx_file_private_header ),
            sizeof( LvxFilePrivateHeader ) );
    _cur_offset += sizeof( LvxFilePrivateHeader );

    for ( auto i = 0; i < device_count; i++ )
    {
        memcpy( write_buffer.get() + _cur_offset,
                static_cast<void *>( &_device_info_list[i] ),
                sizeof( LvxDeviceInfo ) );
        _cur_offset += sizeof( LvxDeviceInfo );
    }

    _file.write( static_cast<char *>( write_buffer.get() ), _cur_offset );
}
//=======================================================================================
//void LvxFile::to_file( QList<LvxBasePackDetail>& point_packet_list )
//{
//    uint64_t cur_pos = 0;
//    FrameHeader frame_header = {0};
//    std::unique_ptr<char[]> write_buffer( new char[ write_buf_len ] );

//    frame_header.current_offset = _cur_offset;
//    frame_header.next_offset = _cur_offset + sizeof( FrameHeader );

//    for ( auto it = point_packet_list.begin(); it != point_packet_list.end(); it++ )
//        frame_header.next_offset += it->pack_size;

//    frame_header.frame_index = _cur_frame_index;

//    memcpy( write_buffer.get() + cur_pos,
//            static_cast<void *>( &frame_header ), sizeof( FrameHeader ) );
//    cur_pos += sizeof( FrameHeader );

//    for ( auto it = point_packet_list.begin(); it != point_packet_list.end(); it++ )
//    {
//        if ( cur_pos + it->pack_size >= write_buf_len )
//        {
//            _file.write( static_cast<char*>( write_buffer.get() ), cur_pos );
//            cur_pos = 0;
//            memcpy( write_buffer.get() + cur_pos,
//                    static_cast<void *>( &(*it) ),
//                    it->pack_size );
//            cur_pos += it->pack_size;
//        }

//        else
//        {
//            memcpy( write_buffer.get() + cur_pos,
//                    static_cast<void *>( &(*it) ),
//                    it->pack_size );
//            cur_pos += it->pack_size;
//        }
//    }

//    _file.write( static_cast<char*>( write_buffer.get() ), cur_pos );

//    _cur_offset = frame_header.next_offset;
//    _cur_frame_index++;
//}
//=======================================================================================
void LvxFile::close()
{
    if ( _file.is_open() )
        _file.close();
}
//=======================================================================================
void LvxFile::add_device_info( LvxDeviceInfo& info )
{
    _device_info_list.push_back( info );
}
//=======================================================================================
int LvxFile::device_count()
{
    return _device_info_list.count();
}
//=======================================================================================
//void LvxFile::fill_packet( const Package<LivoxSpherPoint>& data,
//                           LvxBasePackDetail& packet )
//{
//    packet.version = data.version;
//    packet.port_id = data.slot_id;
//    packet.lidar_index = data.lidar_id;
//    packet.rsvd = data.reserved;

//    auto code = data.status_code;
//    packet.error_code = *reinterpret_cast<int32_t*>( &code );

//    packet.timestamp_type = data.timestamp_type;
//    packet.data_type = data.data_type;

//    memcpy(packet.timestamp, &data.timestamp, 8 * sizeof(uint8_t));

//    if ( packet.data_type == 0 )
//    {
//        packet.pack_size = sizeof( LvxBasePackDetail ) - sizeof( packet.raw_point ) -
//                sizeof( packet.pack_size ) + raw_pnt_num * sizeof( LivoxRawPoint );
//        memcpy( packet.raw_point,
//                static_cast<void *>( data.pnts.toVector().data() ),
//                raw_pnt_num * sizeof( LivoxRawPoint ) );
//    }

//    else if( packet.data_type == 1 )
//    {
//        packet.pack_size = sizeof( LvxBasePackDetail ) - sizeof( packet.raw_point ) -
//                sizeof( packet.pack_size ) + raw_pnt_num * sizeof( LivoxSpherPoint );
//        memcpy( packet.raw_point,
//                static_cast<void *>( data.pnts.toVector().data() ),
//                raw_pnt_num * sizeof( LivoxSpherPoint ) );
//    }
//}
//=======================================================================================
