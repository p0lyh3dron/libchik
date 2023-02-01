/*
 *    dl.h    --    header for loading dynamic libraries
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    Included here is a simple interface for loading dynamic
 *    libraries regardless of platform.
 */
#pragma once

#if __unix__
#define DL_EXTENSION ".so"
#include <dlfcn.h>
#elif _WIN32
#define DL_EXTENSION ".dll"
#include <windows.h>
#else
#error "Platform does not support dynamic libraries."
#endif /* __unix__  */

#include "types.h"

/*
 *    Opens a dynamic library.
 *
 *    @param s8 *path            The path to the library.
 *
 *    @return dl_handle_t    The handle to the library.
 *                           NULL if the library could not be opened.
 *                           The handle should be freed with dl_close.
 */
dl_handle_t dl_open(const s8 *path);

/*
 *    Closes a dynamic library.
 *
 *    @param dl_handle_t handle     The handle to the library.
 */
void dl_close(dl_handle_t handle);

/*
 *    Loads a symbol from a dynamic library.
 *
 *    @param dl_handle_t handle     The handle to the library.
 *    @param s8 *name               The name of the symbol to load.
 *
 *    @return void *         The address of the symbol.
 *                           NULL if the symbol could not be loaded.
 */
void *dl_sym(dl_handle_t handle, const s8 *name);

/*
 *    Returns the last error that occurred
 *    while loading a dynamic library.
 *
 *    @return s8 *           The last error that occurred.
 */
s8 *dl_error(void);