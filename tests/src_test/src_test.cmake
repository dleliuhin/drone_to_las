#========================================================================================

include_directories( ${CMAKE_CURRENT_LIST_DIR} )

#========================================================================================

include( ${CMAKE_CURRENT_LIST_DIR}/../../src/src.cmake )

#========================================================================================

include( ${CMAKE_CURRENT_LIST_DIR}/core_test/core_test.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/pack_test/pack_test.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/config_test/config_test.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/publish_test/publish_test.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/subscribe_test/subscribe_test.cmake )

#========================================================================================

set( SRC_TEST
    ${SRC}
    ${CORE_TEST}
    ${PACK_TEST}
    ${CONFIG_TEST}
    ${PUBLISH_TEST}
    ${SUBSCRIBE_TEST} )

#========================================================================================
