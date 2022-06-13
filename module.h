/*
 *    module.h    --    header stub for module usage
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on April 17, 2022
 * 
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 * 
 *    This short file includes a define for Chik modules
 *    for easier interfacing with the engine.
 */
#pragma once

#include "types.h"
#include "log.h"

/*
 *    Defines this module's entry point.
 *
 *    @param void *    The engine's function table.
 * 
 *    @return u32      The module's return code.
 */

#define CHIK_MODULE( initFunc )                                  \
void *( *engine_load_function )( const s8 * ) = 0;               \
                                                                 \
u32 chik_module_entry( void *spTable ) {                         \
    if ( spTable == nullptr ) {                                  \
        log_error( "Failed to load module.\n" );                 \
        return 0;                                                \
    }                                                            \
                                                                 \
    engine_load_function = ( void *( * )( const s8 * ) )spTable; \
                                                                 \
    initFunc();                                                  \                                                               
    return 1;                                                    \
}                                                                \

/*
 *    The above macro is used to define an engine module.
 *    In essence, this gives each module a function table
 *    that can be used to look up functions loaded
 *    by the engine. Since we're using low-level C,
 *    this seems to work best for allowing modules to
 *    communicate with eachother.
 * 
 *    To use this macro, simply start your module's
 *    main .c file with the macro.
 */