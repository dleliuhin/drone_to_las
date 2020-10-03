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

//=======================================================================================
Decode::Decode( const Config& conf )
    : _conf ( conf                )
{
    _pack.clear();

    _pos( _conf.receive.pos );
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
    vbyte_buffer_view view( data.data(), uint( data.size() ) );

    vdeb << view.show_tail();

    file.close();
}
//=======================================================================================
void Decode::_lvx( const std::string& path )
{
    QFile file( path.c_str() );
    file.open( QIODevice::OpenModeFlag::ReadOnly );

    file.close();
}
//=======================================================================================
