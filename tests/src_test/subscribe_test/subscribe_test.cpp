/*! \file subscribe_test.cpp
 * \brief SubscribeTest class implementation.

 * \authors Dmitrii Leliuhin
 * \date July 2020
 */

//=======================================================================================

#include "subscribe_test.h"
#include "subscribe.h"
#include "publish.h"
#include "config.h"

//=======================================================================================
/*! \test TEST( SubscribeTest, test_constructor )
 * \brief Various constructors.
 */
TEST( SubscribeTest, test_constructor )
{
    Subscribe sub1;
    Config conf;
    Subscribe sub2( conf );
}
//=======================================================================================
/*! \test TEST( SubscribeTest, test_receive )
 * \brief Receive ZCM message.
 */
TEST( SubscribeTest, test_receive )
{
    Config config;
    auto channel = "TestChannel";
    config.send.channel.full = channel;
    config.receive.channel.full = channel;

    Subscribe sub( config );

    Publish pub( config );
    pub.send(0);
}
//=======================================================================================
