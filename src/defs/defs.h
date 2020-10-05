/*! \file defs.h
 * \brief List of common definitions.
 *
 * \authors Dmitrii Leliuhin
 * \date July 2020
 */

//=======================================================================================

#pragma once

#include <sys/types.h>

#include "livox_def.h"

#include <string>
#include <vector>
#include <list>

//=======================================================================================

using VecInt = std::vector<int>;
using VecBln = std::vector<bool>;
using VecFlt = std::vector<float>;
using VecDbl = std::vector<double>;

//=======================================================================================

#define kMaxPointSize 1500

#pragma pack(1)

typedef struct
{
    uint8_t device_index;
    uint8_t version;
    uint8_t port_id;
    uint8_t lidar_index;
    uint8_t rsvd;
    uint32_t error_code;
    uint8_t timestamp_type;
    uint8_t data_type;
    uint8_t timestamp[8];
    uint8_t raw_point[kMaxPointSize];
    uint32_t pack_size;

} LvxBasePackDetail;

#pragma pack()

//=======================================================================================
