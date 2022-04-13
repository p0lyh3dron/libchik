cmake_minimum_required( VERSION 3.10 )

Project( LibChik VERSION 1.0 )

file( GLOB SRC_FILES *.c )

get_property( CHIK_GAMES GLOBAL PROPERTY CHIK_GAMES )
get_property( LIBCHIK GLOBAL PROPERTY LIBCHIK )

link_libraries( dl m )

set( CMAKE_POSITION_INDEPENDENT_CODE ON )
add_library( LibChik SHARED ${SRC_FILES} )

set_target_properties(
    LibChik PROPERTIES
    OUTPUT_NAME chik

    RUNTIME_OUTPUT_NAME chik
    LIBRARY_OUTPUT_NAME chik

    RUNTIME_OUTPUT_DIRECTORY ${CHIK_GAMES}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CHIK_GAMES}/bin
)