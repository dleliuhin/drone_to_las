/*! \file config.h
 * \brief Config class interface.
 *
 * Configuration file parser.
 *
 * \authors Dmitrii Leliuhin
 * \date July 2020
 */

//=======================================================================================

#pragma once

#include "vlog.h"
#include "vsettings.h"

//=======================================================================================

static constexpr uint32_t log_size = 1e6;
static constexpr uint16_t log_rotates = 3U;

//=======================================================================================
/*! \struct Channel
 * \param prefix ZCM channel prefix.
 * \param name   ZCM channel name.
 * \param full   Concatenated prefix and name strings.
 */
struct Channel
{
    std::string prefix;
    std::string name;
    std::string full;
};
//=======================================================================================


//=======================================================================================
/*! \class Config
 * \brief Configuration file parser class.
 */
class Config
{
public:

    //! \details Build default settings if cannot parse them from config.
    Config();

    //! \details Default Config deconstructor.
    ~Config() = default;

    //-----------------------------------------------------------------------------------

    /*! \struct Main
     * \param str Struct name.
     * \param debug Flag if need trace service info to log file.
     */
    struct Main
    {
        const std::string str = "main";

        bool debug { false };

    } main;

    //-----------------------------------------------------------------------------------

    /*! \struct Receive
     * \param str     Struct name.
     * \param target  Inter Process Communications.
     * \param channel ZCM data from channel.
     */
    struct Receive
    {
        const std::string str { "receive" };

        std::string target { "ipc" };

        Channel channel;

    } receive;

    //-----------------------------------------------------------------------------------

    /*! \struct Send
     * \param str     Struct name.
     * \param target  Inter Process Communications.
     * \param channel ZCM data to channel.
     */
    struct Send
    {
        const std::string str { "send" };

        std::string target { "ipc" };

        Channel channel;

    } send;

    //-----------------------------------------------------------------------------------

    /*! \struct Logs
     * \param str          Struct name.
     * \param shared_name  Shared log filename.
     * \param leveled_path Leveled logs path.
     * \param file_sizes   Log max size in Kb.
     * \param rotates      Max logs count.
     * \param need_trace   Flag if need log service messages to file.
     * \param need_shared  Flag if need write all logging levels to one file.
     * \param need_leveled Flag if need write each level of logging to its own file.
     */
    struct Logs
    {
        const std::string str { "logs" };

        std::string shared_name = "$$FULL_APP.log";
        std::string leveled_path = "$$APP_PATH/logs";

        uint32_t file_sizes { log_size };
        uint16_t rotates { log_rotates };

        bool need_trace   { true };
        bool need_shared  { true };
        bool need_leveled { true };

        //-------------------------------------------------------------------------------

        /*! \fn void setup();
         * \brief Starts log data.
         * \details Check Logs flags and run logging if need.
         */
        void setup();

    } logs;

    //-----------------------------------------------------------------------------------

    /*! \fn void capture( const vsettings& data );
     * \brief Fill internal schema.
     * \param[in] data Third-party settings.
     */
    void capture( const vsettings& data );

    /*! \fn static vsettings by_default();
     * \brief Generates config with default settings.
     * \return Default settings.
     */
    static vsettings by_default();

    //-----------------------------------------------------------------------------------

private:

    //! \brief Container of configuration file groups and subgroups.
    vsettings::schema _schema;

    //-----------------------------------------------------------------------------------

    /*! \fn void _fill_ch();
     * \brief Fill receive/send channels fullnames.
     */
    void _fill_ch();

};
//=======================================================================================
