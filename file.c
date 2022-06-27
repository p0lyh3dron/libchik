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

#include "log.h"

s8 gpPaths[ LIBCHIK_FILE_MAX_PATHS ][ LIBCHIK_FILE_MAX_PATH_LENGTH ] = { { 0 } };

/*
 *    Initialize the filesystem with the given search paths.
 *
 *    @param const s8 *    The search paths to use.
 *    @param ...           The search paths to use.
 */
void filesystem_init( const s8 *spPaths, ... ) {
    va_list apPaths;
    va_start( apPaths, spPaths );
    s64 i;
    for( i = 0; i < LIBCHIK_FILE_MAX_PATHS; i++ ) {
        if( spPaths == nullptr ) {
            break;
        }
        strcpy( gpPaths[ i ], spPaths );
        spPaths = va_arg( apPaths, const s8 * );
    }
    va_end( apPaths );
}

/*
 *    Add a search path to the filesystem.
 *
 *    @param const s8 *    The search path to add.
 */
void filesystem_add_search_path( const s8 *spPath ) {
    s64 i;
    for( i = 0; i < LIBCHIK_FILE_MAX_PATHS; i++ ) {
        if( gpPaths[ i ][ 0 ] == 0 ) {
            strcpy( gpPaths[ i ], spPath );
            return;
        }
    }
}

/*
 *    Open a file and read it into memory.
 *
 *    @param const s8 *    The file to open.
 *    @param u32 *         The size of the file.
 * 
 *    @return s8 *         The file contents.
 */
s8 *file_read( const s8 *spFile, u32 *spSize ) {
    FILE *pF = nullptr;

    s8  buf[ LIBCHIK_FILE_MAX_PATH_LENGTH ];
    s64 i;
    for( i = 0; i < LIBCHIK_FILE_MAX_PATHS; i++ ) {
        if( gpPaths[ i ][ 0 ] == 0 ) {
            break;
        }
        sprintf( buf, "%s/%s", gpPaths[ i ], spFile );
        pF = fopen( buf, "rb" );
        if( pF != nullptr ) {
            break;
        }
    }

    if( pF == nullptr ) {
        log_error( "Could not open file '%s'", spFile );
        return nullptr;
    }

    fseek( pF, 0, SEEK_END );
    *spSize = ftell( pF );
    fseek( pF, 0, SEEK_SET );
    s8 *spData = ( s8 * )malloc( *spSize );
    fread( spData, 1, *spSize, pF );
    fclose( pF );
    return spData;
}

/*
 *   Free a file that was read into memory.
 *   Alternatively, you can use free() to free the file.
 *
 *   @param s8 *          The file to free.
 */
void file_free( s8 *spFile ) {
    free( spFile );
}