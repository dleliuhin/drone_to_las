/*! \file subscribe.cpp
 * \brief Subscribe class implementation.
 *
 * \authors Dmitrii Leliuhin
 * \date July 2020
 */

//=======================================================================================

#include "subscribe.h"

#include "vtime_point.h"

//=======================================================================================
Subscribe::Subscribe( const Config& conf )
    : _conf ( conf                )
{
    _pack.clear();
}
//=======================================================================================
