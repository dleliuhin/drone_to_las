#========================================================================================

project( test_cservice_template )

#========================================================================================

cmake_minimum_required( VERSION 3.15 )

#========================================================================================

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage" )

#========================================================================================

include( ${CMAKE_CURRENT_SOURCE_DIR}/../external/external.cmake )

#========================================================================================

find_library( GTEST_LIBRARY NAMES libgtest.a PATHS ${EXT_LIBS_PATH} )
set( ${PROJECT_NAME} -lgtest -lgcov -fprofile-arcs )

#========================================================================================

include_directories( ${CMAKE_SOURCE_DIR} )

include( ${CMAKE_CURRENT_SOURCE_DIR}/src_test/src_test.cmake )

#========================================================================================

add_executable( ${PROJECT_NAME}
    src_test/test.cpp
    ${SRC_TEST}
    ${EXTERNAL}
    ${GTEST_LIBRARY} )

target_link_libraries( ${PROJECT_NAME}
    ${V_LIBRARIES}
    ${GTEST_LIBRARY}
    -lstdc++fs
    -ldl )

#========================================================================================

unset ( QT_QMAKE_EXECUTABLE )

#========================================================================================
