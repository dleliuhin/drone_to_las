#include "livox_sdk.h"

#include <QObject>

#include <condition_variable>
#include <memory>
#include <cstring>
#include <fstream>
#include <list>
#include <vector>
#include <mutex>

//=======================================================================================

static const std::string livox_tech = "livox_tech";
static constexpr auto kDefaultFrameDurationTime = 50;
static constexpr auto magic_code = 0xac0ea767;
static constexpr auto frame_rate = 20;
static constexpr auto max_shutter = 3000; // milliseconds

//=======================================================================================

typedef enum
{
    kDeviceStateDisconnect = 0,
    kDeviceStateConnect = 1,
    kDeviceStateSampling = 2

} DeviceState;

//=======================================================================================

typedef struct
{
    uint8_t handle;
    DeviceState device_state;
    DeviceInfo info;

} DeviceItem;

#pragma pack(1)

//=======================================================================================

typedef struct
{
    uint8_t signature[16];
    uint8_t version[4];
    uint32_t magic_code;

} LvxFilePublicHeader;

//=======================================================================================

typedef struct
{
    uint32_t frame_duration;
    uint8_t device_count;

} LvxFilePrivateHeader;

//=======================================================================================

typedef struct
{
    uint8_t lidar_broadcast_code[16];
    uint8_t hub_broadcast_code[16];
    uint8_t device_index;
    uint8_t device_type;
    uint8_t extrinsic_enable;
    float roll;
    float pitch;
    float yaw;
    float x;
    float y;
    float z;

} LvxDeviceInfo;

//=======================================================================================

typedef struct
{
    uint64_t current_offset;
    uint64_t next_offset;
    uint64_t frame_index;

} FrameHeader;

#pragma pack()
//=======================================================================================


//=======================================================================================
class LvxFile
{
public:

    LvxFile();

    bool open( const QString& path );
    void close();

    void init_header();
//    void to_file( QList<LvxBasePackDetail>& point_packet_list_temp );

    void add_device_info( LvxDeviceInfo& info );

    int device_count();

//    static void fill_packet( const Package<LivoxSpherPoint>& data,
//                             LvxBasePackDetail& packet );

    //-----------------------------------------------------------------------------------

private:

    std::ofstream _file;

    QList<LvxDeviceInfo> _device_info_list;

    uint32_t _cur_frame_index;
    uint32_t _frame_duration;
    uint64_t _cur_offset;

};
//=======================================================================================

