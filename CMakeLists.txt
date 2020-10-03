#========================================================================================

project( lvx_to_las
    LANGUAGES CXX )

#========================================================================================

cmake_minimum_required( VERSION 3.10 )

#========================================================================================

option( GUI FALSE )

if ( GUI )
    set( CMAKE_BUILD_TYPE "Debug" )
    add_definitions( -DGUI )
else()
    set( CMAKE_BUILD_TYPE "Release" )
endif()

#========================================================================================

option( V_DEVELOP FALSE )

if ( V_DEVELOP )
    add_definitions( -DV_DEVELOP )
endif()

#========================================================================================

set( CMAKE_AUTOUIC ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

#========================================================================================

include( ${CMAKE_CURRENT_SOURCE_DIR}/external/external.cmake )

#========================================================================================

include_directories( ${CMAKE_SOURCE_DIR} )

include( ${CMAKE_CURRENT_SOURCE_DIR}/cfg/cfg.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/src/src.cmake )

#========================================================================================

find_package( Qt5Core )

add_executable( ${PROJECT_NAME}
    src/main.cpp
    ${CFG}
    ${SRC}
    ${EXTERNAL} )

target_link_libraries( ${PROJECT_NAME}
    ${VTK_LIBRARIES}
    ${PCL_LIBRARIES}
    ${V_LIBRARIES}
    Qt5::Core
    -ldl )

#========================================================================================
