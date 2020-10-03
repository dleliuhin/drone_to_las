#========================================================================================

set( VLIBS_DIR ${CMAKE_CURRENT_LIST_DIR}/VLib/src )

#========================================================================================

include_directories( ${VLIBS_DIR}/src )
include_directories( ${VLIBS_DIR}/src/cmake )

#========================================================================================

include( ${VLIBS_DIR}/cmake/vsettings.cmake )
include( ${VLIBS_DIR}/cmake/pthread.cmake )
include( ${VLIBS_DIR}/cmake/vsignal.cmake )
include( ${VLIBS_DIR}/cmake/vchrono.cmake )
include( ${VLIBS_DIR}/cmake/vposix.cmake )
include( ${VLIBS_DIR}/cmake/vgit.cmake )
include( ${VLIBS_DIR}/cmake/vlog.cmake )

#========================================================================================

set( V_LIBS
    ${V_HEADERS}
    ${V_SOURCES} )

#========================================================================================
