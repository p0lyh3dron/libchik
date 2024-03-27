cmake_minimum_required( VERSION 3.10 )

Project( LibChik VERSION 1.0 )

set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

file( GLOB SRC_FILES *.c *h )

get_property( CHIK_GAMES GLOBAL PROPERTY CHIK_GAMES )
get_property( LIBCHIK GLOBAL PROPERTY LIBCHIK )

if ( ${PLATFORM} MATCHES "Win64" )
    set( LIBCHIK_OUT ${CHIK_GAMES} )
endif()

set( CMAKE_POSITION_INDEPENDENT_CODE ON )
add_library( LibChik SHARED ${SRC_FILES} )

message("Plaftfomr: ${PLATFORM}" )
message("LIBCHIK_OUT: ${LIBCHIK_OUT}" )

if ( ${PLATFORM} MATCHES "Linux64" )
    set( LIBCHIK_OUT ${CHIK_GAMES}/bin )
    link_libraries( dl pthread )
    target_link_libraries( LibChik m )
endif()

set_target_properties(
    LibChik PROPERTIES
    OUTPUT_NAME chik

    RUNTIME_OUTPUT_NAME chik
    LIBRARY_OUTPUT_NAME chik

    RUNTIME_OUTPUT_DIRECTORY ${LIBCHIK_OUT}
    LIBRARY_OUTPUT_DIRECTORY ${LIBCHIK_OUT}
)

# set output directories for all builds (Debug, Release, etc.)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set_target_properties(
    	LibChik PROPERTIES
    	RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIBCHIK_OUT}
    	LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIBCHIK_OUT}
    )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
