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

char _paths[LIBCHIK_FILE_MAX_PATHS][LIBCHIK_FILE_MAX_PATH_LENGTH] = {{0}};

/*
 *    Initialize the filesystem with the given search paths.
 *
 *    @param const char *paths    The search paths to use.
 *    @param ...                The search paths to use.
 */
void filesystem_init(const char *paths, ...) {
    unsigned long i;
    va_list       paths_va;

    va_start(paths_va, paths);
    for (i = 0; i < LIBCHIK_FILE_MAX_PATHS; i++) {
        if (paths == nullptr) {
            break;
        }
        strcpy(_paths[i], paths);
        paths = va_arg(paths_va, const char *);
    }
    va_end(paths_va);
}

/*
 *    Add a search path to the filesystem.
 *
 *    @param const char *path    The search path to add.
 */
void filesystem_add_search_path(const char *path) {
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
 *    @param const char *file    The file to open.
 *    @param unsigned int *size         The size of the file.
 *
 *    @return char *         The file contents.
 */
char *file_read(const char *file, unsigned int *size) {
    unsigned long i;
    FILE         *pF;
    char          buf[LIBCHIK_FILE_MAX_PATH_LENGTH];
    char         *data;

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
        VLOGF_ERR("Could not open file '%s'", file);
        return nullptr;
    }

    fseek(pF, 0, SEEK_END);
    *size = ftell(pF);
    fseek(pF, 0, SEEK_SET);
    data = (char *)malloc(*size);
    if (fread(data, 1, *size, pF) != *size) {
        VLOGF_ERR("Could not read file '%s'", file);
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
 *   @param char *file          The file to free.
 */
void file_free(char *file) { free(file); }