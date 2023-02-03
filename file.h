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
#ifndef LIBCHIK_FILE_H
#define LIBCHIK_FILE_H

#define LIBCHIK_FILE_MAX_PATH_LENGTH 1024
#define LIBCHIK_FILE_MAX_PATHS       256

#include "types.h"

/*
 *    Initialize the filesystem with the given search paths.
 *
 *    @param const s8 *paths    The search paths to use.
 *    @param ...                The search paths to use.
 */
void filesystem_init(const s8 *paths, ...);

/*
 *    Add a search path to the filesystem.
 *
 *    @param const s8 *path    The search path to add.
 */
void filesystem_add_search_path(const s8 *path);

/*
 *    Open a file and read it into memory.
 *
 *    @param const s8 *file    The file to open.
 *    @param u32 *size         The size of the file.
 *
 *    @return s8 *         The file contents.
 */
s8 *file_read(const s8 *file, u32 *size);

/*
 *   Free a file that was read into memory.
 *   Alternatively, you can use free() to free the file.
 *
 *   @param s8 *file          The file to free.
 */
void file_free(s8 *file);

#endif /* LIBCHIK_FILE_H  */