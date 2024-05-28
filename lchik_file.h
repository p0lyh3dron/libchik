/*
 *    lchik_file.h    --    file handling functions
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

#include <sys/stat.h>

#include "lchik_types.h"

typedef struct {
    char         path[LIBCHIK_FILE_MAX_PATH_LENGTH];
    struct stat  stat;
    void       (*callback)();
} watched_file_t;

/*
 *    Initialize the filesystem with the given search paths.
 *
 *    @param const char *paths    The search paths to use.
 *    @param ...                The search paths to use.
 */
void filesystem_init(const char *paths, ...);

/*
 *    Add a search path to the filesystem.
 *
 *    @param const char *path    The search path to add.
 */
void filesystem_add_search_path(const char *path);

/*
 *    Open a file and read it into memory.
 *
 *    @param const char *file    The file to open.
 *    @param unsigned int *size         The size of the file.
 *
 *    @return char *         The file contents.
 */
char *file_read(const char *file, unsigned int *size);

/*
 *    Updates a watched file.
 *
 *    @param watched_file_t *file    The file to update.
 * 
 *    @return int                     0 on success, -1 on failure.
 */
int file_update(watched_file_t *file);

/*
 *    Creates a watched file.
 *
 *    @param watched_file_t *file    The object to create.
 *    @param const char *path        The path to the file.
 *    @param void (*callback)(void *) The callback to call when the file is updated.
 * 
 *    @return int                     0 on success, -1 on failure.
 */
int file_create(watched_file_t *file, const char *path, void (*callback)(void *));

/*
 *    Deletes a normal file.
 *
 *    @param const char *path    The path to the file.
 * 
 *    @return int                 0 on success, -1 on failure.
 */
int file_delete(const char *path);

/*
 *   Free a file that was read into memory.
 *   Alternatively, you can use free() to free the file.
 *
 *   @param char *file          The file to free.
 */
void file_free(char *file);



#endif /* LIBCHIK_FILE_H  */