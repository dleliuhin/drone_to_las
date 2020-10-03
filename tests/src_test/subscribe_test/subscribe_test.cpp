/*! \file decode_test.cpp
 * \brief DecodeTest class implementation.

 * \authors Dmitrii Leliuhin
 * \date July 2020
 */

//=======================================================================================

#include "decode_test.h"
#include "decode.h"
#include "publish.h"
#include "config.h"

//=======================================================================================
/*! \test TEST( DecodeTest, test_constructor )
 * \brief Various constructors.
 */
TEST( DecodeTest, test_constructor )
{
    Decode sub1;
    Config conf;
    Decode sub2( conf );
}
//=======================================================================================
/*! \test TEST( DecodeTest, test_receive )
 * \brief Receive ZCM message.
 */
TEST( DecodeTest, test_receive )
{
    Config config;
    auto channel = "TestChannel";
    config.send.channel.full = channel;
    config.receive.channel.full = channel;

    Decode sub( config );

    Publish pub( config );
    pub.send(0);
}
//=======================================================================================
