/*! \file pack.h
 * \brief Data package from multiple sensors.
 *
 * \authors Dmitrii Leliuhin
 * \date July 2020
 */

//=======================================================================================

#pragma once

#include "defs.h"

#include <list>
#include <map>

//=======================================================================================
struct PosData
{
    double timestamp {0.};
    double longitude {0.};
    double latitude {0.};
    double height {0.};
    double roll {0.};
    double pitch {0.};
    double yaw {0.};
    double easting {0.};
    double northing {0.};

    uint32_t timestamp_ms {0};
};
//=======================================================================================


//=======================================================================================
/*! \struct Pack
 * \param data ZCM data entry.
 */
class Pack
{
public:

    std::map<uint64_t, PosData> pos;
    std::map<uint64_t, LivoxPoint> lvx;

    //-----------------------------------------------------------------------------------

    /*! \fn void clear();
     * \brief Clear all data entries.
     */
    void clear();

};
//=======================================================================================
