/*! \file publish_test.cpp
 * \brief PublishTest class implementation.

 * \authors Dmitrii Leliuhin
 * \date July 2020
 */

//=======================================================================================

#include "publish_test.h"
#include "publish.h"
#include "config.h"

//=======================================================================================
/*! \test TEST( PublishTest, test_constructor )
 * \brief Various constructors.
 */
TEST( PublishTest, test_constructor )
{
    Publish pub1;
    Config config;
    Publish pub2( config );
}
//=======================================================================================
/*! \test TEST( PublishTest, test_send )
 * \brief send to ZCM.
 */
TEST( PublishTest, test_send )
{
    Config conf;
    conf.send.channel.full = "OutChannel";

    Publish publisher( conf );

    publisher.send(0);
}
//=======================================================================================
