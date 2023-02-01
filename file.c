/*
 *    file.h    --    file handling functions
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on June 25, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    The filesystem handles file reading and writing, as well
 *    as a search path lookup.
 */
#include "file.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "log.h"

s8 _paths[LIBCHIK_FILE_MAX_PATHS][LIBCHIK_FILE_MAX_PATH_LENGTH] = {{0}};

/*
 *    Initialize the filesystem with the given search paths.
 *
 *    @param const s8 *paths    The search paths to use.
 *    @param ...                The search paths to use.
 */
void filesystem_init(const s8 *paths, ...) {
    unsigned long i;
    va_list paths_va;

    va_start(paths_va, paths);
    for (i = 0; i < LIBCHIK_FILE_MAX_PATHS; i++) {
        if (paths == nullptr) {
            break;
        }
        strcpy(_paths[i], paths);
        paths = va_arg(paths_va, const s8 *);
    }
    va_end(paths_va);
}

/*
 *    Add a search path to the filesystem.
 *
 *    @param const s8 *path    The search path to add.
 */
void filesystem_add_search_path(const s8 *path) {
    unsigned long i;

    for (i = 0; i < LIBCHIK_FILE_MAX_PATHS; i++) {
        if (_paths[i][0] == 0) {
            strcpy(_paths[i], path);
            return;
        }
    }
}

/*
 *    Open a file and read it into memory.
 *
 *    @param const s8 *file    The file to open.
 *    @param u32 *size         The size of the file.
 *
 *    @return s8 *         The file contents.
 */
s8 *file_read(const s8 *file, u32 *size) {
    unsigned long i;
    FILE *pF;
    char buf[LIBCHIK_FILE_MAX_PATH_LENGTH];
    char *data;
    
    for (i = 0; i < LIBCHIK_FILE_MAX_PATHS; i++) {
        if (_paths[i][0] == 0) {
            break;
        }
        sprintf(buf, "%s/%s", _paths[i], file);
        pF = fopen(buf, "rb");
        if (pF != nullptr) {
            break;
        }
    }

    if (pF == nullptr) {
        log_error(
            "s8 *file_read( const s8 *, u32 * ): Could not open file '%s'",
            file);
        return nullptr;
    }

    fseek(pF, 0, SEEK_END);
    *size = ftell(pF);
    fseek(pF, 0, SEEK_SET);
    data = (s8 *)malloc(*size);
    if (fread(data, 1, *size, pF) != *size) {
        log_error(
            "s8 *file_read( const s8 *, u32 * ): Could not read file '%s'",
            file);
        free(data);
        return nullptr;
    }
    fclose(pF);
    return data;
}

/*
 *   Free a file that was read into memory.
 *   Alternatively, you can use free() to free the file.
 *
 *   @param s8 *file          The file to free.
 */
void file_free(s8 *file) { free(file); }