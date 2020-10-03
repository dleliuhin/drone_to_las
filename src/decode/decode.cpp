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

    _pos_data.clear();

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

        _pos_data.push_back( tmp );
    }
}
//=======================================================================================
void Decode::_lvx( const std::string& path )
{
    QFile file( path.c_str() );
    file.open( QIODevice::OpenModeFlag::ReadOnly );

    file.close();
}
//=======================================================================================
