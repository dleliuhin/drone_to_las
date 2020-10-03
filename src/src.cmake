#========================================================================================

include_directories( ${CMAKE_CURRENT_LIST_DIR} )

#========================================================================================

include( ${CMAKE_CURRENT_LIST_DIR}/core/core.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/defs/defs.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/pack/pack.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/config/config.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/publish/publish.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/subscribe/subscribe.cmake )

if ( GUI )
    include( ${CMAKE_CURRENT_LIST_DIR}/plot/plot.cmake )
endif()

#========================================================================================

set( SRC
    ${CORE}
    ${DEFS}
    ${PACK}
    ${PLOT}
    ${CONFIG}
    ${PUBLISH}
    ${SUBSCRIBE} )

#========================================================================================
