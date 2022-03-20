/*
 *    dl.c    --    source for loading dynamic libraries
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 * 
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 * 
 *    Included here are the definitions for loading dynamic
 *    libraries regardless of platform.
 */
#include "dl.h"

/*
 *    Opens a dynamic library.
 *
 *    @param s8 *            The path to the library.
 *
 *    @return dl_handle_t    The handle to the library.
 *                           NULL if the library could not be opened.
 *                           The handle should be freed with dl_close.
 */
dl_handle_t dl_open( const s8 *spPath ) {
#if __unix__
    return dlopen( spPath, RTLD_LAZY );
#elif _WIN32
    return LoadLibrary( spPath );
#endif /* __unix__  */
}

/*
 *    Closes a dynamic library.
 *
 *    @param dl_handle_t     The handle to the library.
 */
void dl_close( dl_handle_t sHandle ) {
#if __unix__
    dlclose( sHandle );
#elif _WIN32
    FreeLibrary( sHandle );
#endif /* __unix__  */
}

/*
 *    Loads a symbol from a dynamic library.
 *
 *    @param dl_handle_t     The handle to the library.
 *    @param s8 *            The name of the symbol to load.
 * 
 *    @return void *         The address of the symbol.
 *                           NULL if the symbol could not be loaded.
 */
void *dl_load( dl_handle_t sHandle, const s8 *spName ) {
#if __unix__
    return dlsym( sHandle, spName );
#elif _WIN32
    return GetProcAddress( sHandle, spName );
#endif /* __unix__  */
}