cmake_minimum_required( VERSION 3.10 )

Project( LibChik VERSION 1.0 )

file( GLOB SRC_FILES *.c )

add_library( LibChik ${SRC_FILES} )

set_target_properties(
    LibChik PROPERTIES
    OUTPUT_NAME chik
)