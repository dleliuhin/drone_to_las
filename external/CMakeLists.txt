#========================================================================================

cmake_minimum_required( VERSION 3.10 )

project( cservice_template_external )

#========================================================================================

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

include( ${CMAKE_CURRENT_SOURCE_DIR}/vlibs.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/zcm_types.cmake )
include( ${VLIBS_DIR}/cmake/pthread.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/niias_srv_supply/niias_srv_supply.cmake )

add_executable(
    ${PROJECT_NAME}
    ${V_HEADERS}
    ${V_SOURCES}
    )

target_link_libraries( ${PROJECT_NAME} -ldl )

#========================================================================================
