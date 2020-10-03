#========================================================================================

find_package( PCL REQUIRED )

if( PCL_FOUND )

    include_directories( ${PCL_INCLUDE_DIRS} )

    add_definitions( ${PCL_DEFINITIONS} )

    link_directories( ${PCL_LIBRARY_DIRS} )

endif()

find_package( VTK REQUIRED )

include( ${VTK_USE_FILE} )

#========================================================================================

include_directories( ${CMAKE_CURRENT_LIST_DIR} )

#========================================================================================

set( PLOT
    ${CMAKE_CURRENT_LIST_DIR}/view.h
    ${CMAKE_CURRENT_LIST_DIR}/view.cpp
   )

#========================================================================================
