/*! \file config_test.cpp
 * \brief ConfigTest class implementation.

 * \authors Dmitrii Leliuhin
 * \date July 2020
 */

//=======================================================================================

#include "config_test.h"
#include "config.h"

#include <filesystem>

//=======================================================================================
/*! \test \fn void check_default_settings( const Config& conf )
 * \brief check_default_settings
 * \param conf Internal Config.
 */
void check_default_settings( const Config& conf )
{
    ASSERT_EQ( false, conf.main.debug );
    ASSERT_EQ( "main", conf.main.str );

    ASSERT_EQ( "ipc",     conf.receive.target );
    ASSERT_EQ( "",        conf.receive.channel.prefix );
    ASSERT_EQ( "",        conf.receive.channel.name );
    ASSERT_EQ( "",        conf.receive.channel.full );
    ASSERT_EQ( "receive", conf.receive.str );

    ASSERT_EQ( "ipc",  conf.send.target );
    ASSERT_EQ( "",     conf.send.channel.prefix );
    ASSERT_EQ( "",     conf.send.channel.name );
    ASSERT_EQ( "",     conf.send.channel.full );
    ASSERT_EQ( "send", conf.send.str );

    ASSERT_EQ( true,              conf.logs.need_trace );
    ASSERT_EQ( true,              conf.logs.need_shared );
    ASSERT_EQ( "$$FULL_APP.log",  conf.logs.shared_name );
    ASSERT_EQ( true,              conf.logs.need_leveled );
    ASSERT_EQ( "$$APP_PATH/logs", conf.logs.leveled_path );
    ASSERT_EQ( 1e6,               conf.logs.file_sizes );
    ASSERT_EQ( log_rotates,       conf.logs.rotates );
    ASSERT_EQ( "logs",            conf.logs.str );
}
//=======================================================================================


//=======================================================================================
/*! \test TEST( ConfigTest, test_structs )
 * \brief Default Config structs.
 */
TEST( ConfigTest, test_structs )
{
    Config conf;

    check_default_settings( conf );
}
//=======================================================================================
/*! \test TEST( ConfigTest, test_capture )
 * \brief Capture internal vsettings.
 */
TEST( ConfigTest, test_capture )
{
    Config conf;
    conf.capture( Config().by_default() );

    check_default_settings( conf );
}
//=======================================================================================
/*! \test TEST( ConfigTest, test_by_default )
 * \brief Default Config vsettings.
 */
TEST( ConfigTest, test_by_default )
{
    auto settings = Config::by_default();

    ASSERT_EQ( "false", settings.subgroup( Config().main.str ).get( "debug" ) );

    ASSERT_EQ( "ipc", settings.subgroup( Config().receive.str ).get( "target" ) );
    ASSERT_EQ( "",    settings.subgroup( Config().receive.str ).get( "prefix" ) );
    ASSERT_EQ( "",    settings.subgroup( Config().receive.str ).get( "name" ) );

    ASSERT_EQ( "ipc", settings.subgroup( Config().send.str ).get( "target" ) );
    ASSERT_EQ( "",    settings.subgroup( Config().send.str ).get( "prefix" ) );
    ASSERT_EQ( "",    settings.subgroup( Config().send.str ).get( "name" ) );

    ASSERT_EQ( "true", settings.subgroup( Config().logs.str ).get( "need_trace" ) );
    ASSERT_EQ( "true", settings.subgroup( Config().logs.str ).get( "need_shared" ) );
    ASSERT_EQ( "$$FULL_APP.log",
               settings.subgroup( Config().logs.str ).get( "shared_name" ) );
    ASSERT_EQ( "true", settings.subgroup( Config().logs.str ).get( "need_leveled" ) );
    ASSERT_EQ( "$$APP_PATH/logs",
               settings.subgroup( Config().logs.str ).get( "leveled_path" ) );
    ASSERT_EQ( std::to_string( log_size ),
               settings.subgroup( Config().logs.str ).get( "file_sizes" ) );
    ASSERT_EQ( std::to_string( log_rotates ),
               settings.subgroup( Config().logs.str ).get( "rotates" ) );
}
//=======================================================================================
/*! \test TEST( ConfigTest, test_setup )
 * \brief Existing log files & dirs;
 */
TEST( ConfigTest, test_setup )
{
    Config conf;

    {
        conf.logs.need_trace = false;
        conf.logs.setup();
        ASSERT_FALSE( std::filesystem::exists( "$$FULL_APP.log" ) );
    }

    {
        conf.logs.need_trace = true;
        conf.logs.setup();
        ASSERT_TRUE( std::filesystem::exists( "$$FULL_APP.log" ) );
        ASSERT_TRUE( std::filesystem::exists( "$$APP_PATH" ) );
        ASSERT_TRUE( std::filesystem::is_directory( "$$APP_PATH" ) );
    }
}
//=======================================================================================
