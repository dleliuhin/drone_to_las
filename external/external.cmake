#========================================================================================

include_directories( ${CMAKE_CURRENT_LIST_DIR} )

#========================================================================================

include( ${CMAKE_CURRENT_LIST_DIR}/vlibs.cmake )
include( ${VLIBS_DIR}/cmake/pthread.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/args_parser/args_parser.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/cpp_codestyle/codestyle.cmake )

#========================================================================================

set( EXTERNAL
    ${V_HEADERS}
    ${V_SOURCES}
    ${CODE_STYLE} )

#========================================================================================
