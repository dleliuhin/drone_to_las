#include "subscribe_test.h"
#include "publish_test.h"
#include "config_test.h"
#include "core_test.h"
#include "pack_test.h"

#include "gtest/gtest.h"

#include <iostream>

//=======================================================================================
int main( int argc, char **argv )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
//=======================================================================================
