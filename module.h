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

#include "log.h"
#include "types.h"

/*
 *    Defines this module's entry point.
 *
 *    @param void *    The engine's function table.
 *
 *    @return u32      The module's return code.
 */

#define CHIK_MODULE(init_func, update_func, exit_func)                         \
    void *(*engine_load_function)(const s8 *) = 0;                             \
                                                                               \
    u32 chik_module_entry(void *table) {                                       \
        if (table == nullptr) {                                                \
            log_error("Failed to load module.\n");                             \
            return 0;                                                          \
        }                                                                      \
                                                                               \
        engine_load_function = (void *(*)(const s8 *))table;                   \
                                                                               \
        u32 (*fun)(void) = &init_func;                                         \
        return fun();                                                          \
    }                                                                          \
                                                                               \
    u32 chik_module_update(f32 dt) {                                           \
        u32 (*fun)(f32) = &update_func;                                        \
        return fun(dt);                                                        \
    }                                                                          \
                                                                               \
    u32 chik_module_exit(void) {                                               \
        u32 (*fun)(void) = &exit_func;                                         \
        return fun();                                                          \
    }

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