/*
 *    lchik_dl.c    --    source for loading dynamic libraries
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    Included here are the definitions for loading dynamic
 *    libraries regardless of platform.
 */
#include "lchik_dl.h"

#if __unix__
#elif _WIN32
#include <windows.h>
#define MAX_ERROR_LENGTH 256
#endif /* __unix__  */

/*
 *    Opens a dynamic library.
 *
 *    @param char * path            The path to the library.
 *
 *    @return dl_handle_t    The handle to the library.
 *                           NULL if the library could not be opened.
 *                           The handle should be freed with dl_close.
 */
dl_handle_t dl_open(const char *path) {
#if __unix__
    return dlopen(path, RTLD_LAZY);
#elif _WIN32
    return LoadLibrary(path);
#endif /* __unix__  */
}

/*
 *    Closes a dynamic library.
 *
 *    @param dl_handle_t handle     The handle to the library.
 */
void dl_close(dl_handle_t handle) {
#if __unix__
    dlclose(handle);
#elif _WIN32
    FreeLibrary(handle);
#endif /* __unix__  */
}

/*
 *    Loads a symbol from a dynamic library.
 *
 *    @param dl_handle_t handle     The handle to the library.
 *    @param char *name               The name of the symbol to load.
 *
 *    @return void *         The address of the symbol.
 *                           NULL if the symbol could not be loaded.
 */
void *dl_sym(dl_handle_t handle, const char *name) {
#if __unix__
    return dlsym(handle, name);
#elif _WIN32
    return GetProcAddress(handle, name);
#endif /* __unix__  */
}

/*
 *    Returns the last error that occurred
 *    while loading a dynamic library.
 *
 *    @return char *           The last error that occurred.
 */
char *dl_error(void) {
#if __unix__
    return dlerror();
#elif _WIN32
    static char error[MAX_ERROR_LENGTH];
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, error,
                  sizeof(error), NULL);
    return error;
#endif /* __unix__  */
}