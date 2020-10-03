/*! \file core.cpp
 * \brief Core class implementation.
 *
 * \authors Dmitrii Leliuhin
 * \date July 2020
 */

//=======================================================================================

#include "core.h"

#include "vlog.h"
#include "vtime_point.h"

//=======================================================================================
Core::Core( const Config& conf )
    : _conf ( conf )
{}
//=======================================================================================


//=======================================================================================
void Core::run( const Pack& pack )
{
    // Algorithms

    processed( pack.data.timestamp() /* Send your data. */ );

#ifdef GUI
    plot_data( /*Transmit needed data.*/ );
#endif
}
//=======================================================================================
