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
#include <dlfcn.h>
#elif _WIN32
#include <windows.h>
#else
#error "Platform does not support dynamic libraries."
#endif /* __unix__  */

#include "types.h"

/*
 *    Opens a dynamic library.
 *
 *    @param s8 *            The path to the library.
 *
 *    @return dl_handle_t    The handle to the library.
 *                           NULL if the library could not be opened.
 *                           The handle should be freed with dl_close.
 */
dl_handle_t dl_open( const s8 *spPath );

/*
 *    Closes a dynamic library.
 *
 *    @param dl_handle_t     The handle to the library.
 */
void dl_close( dl_handle_t sHandle );

/*
 *    Loads a symbol from a dynamic library.
 *
 *    @param dl_handle_t     The handle to the library.
 *    @param s8 *            The name of the symbol to load.
 * 
 *    @return void *         The address of the symbol.
 *                           NULL if the symbol could not be loaded.
 */
void *dl_load( dl_handle_t sHandle, const s8 *spName );