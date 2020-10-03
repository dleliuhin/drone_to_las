/*! \file subscribe.h
 * \brief Subscribe class interface.
 *
 * ZCM message subscriber.
 *
 * \authors Dmitrii Leliuhin
 * \date July 2020
 */

//=======================================================================================

#pragma once

#include "config.h"
#include "pack.h"

#include "vsignal.h"

//=======================================================================================
/*! \class Subscribe
 * \brief ZCM message subscriber class.
 */
class Subscribe
{
public:

    /*!
     * \param[in] conf Configuration settings.
     * \details Initialize _zcm node
     */
    Subscribe( const Config& conf = {} );

    //! \brief default destructor.
    ~Subscribe() = default;

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

};
//=======================================================================================
