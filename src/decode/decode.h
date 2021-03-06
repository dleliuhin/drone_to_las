/*! \file decode.h
 * \brief Decode class interface.
 *
 * ZCM message decoder.
 *
 * \authors Dmitrii Leliuhin
 * \date July 2020
 */

//=======================================================================================

#pragma once

#include "config.h"
#include "pack.h"

#include "vsignal.h"

#include "lvx_file.h"

#include <cstdlib>
#include <string>
#include <cstdio>
#include <list>

//=======================================================================================
/*! \class Decode
 * \brief ZCM message decoder class.
 */
class Decode
{
public:

    /*!
     * \param[in] conf Configuration settings.
     */
    Decode( const Config& conf = {} );

    //! \brief default destructor.
    ~Decode() = default;

    //-----------------------------------------------------------------------------------

    /*!
     * \brief emit signal if ZCM message received.
     * \param Pack Data from ZCM bus.
     */
    vsignal<Pack> received;

    //-----------------------------------------------------------------------------------

private:

    //! \brief Configuration parameters.
    Config _conf;

    //! \brief Data aggregated from multiple sensors.
    Pack _pack;

    std::map<uint64_t, LidarSetUtcSyncTimeRequest> _test;

    //-----------------------------------------------------------------------------------

    void _pos( const std::string& path );
    void _lvx( const std::string& path );

    int _weekday( const int& d, const int& m, int y );

};
//=======================================================================================
