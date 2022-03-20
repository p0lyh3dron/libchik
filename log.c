/*
 *    log.c    --    source for logging messages.
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 * 
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 * 
 *    Included here are the definitions for logging messages.
 */
#include "log.h"

#include <stdarg.h>

/*
 *    Logs a message to the console.
 *
 *    @param s8 *            The message to log.
 *    @param ...             The arguments to the message.
 */
void log_msg( const s8 *spMessage, ... ) {
    va_list vaArgs;
    s8      pBuffer[ MAX_LOG_MESSAGE_LENGTH ];

    va_start( vaArgs, spMessage );
    vsnprintf( pBuffer, MAX_LOG_MESSAGE_LENGTH, spMessage, vaArgs );
    va_end( vaArgs );

    printf( "%s", pBuffer );
}

/*
 *    Logs a note to the console.
 *
 *    @param s8 *            The note to log.
 *    @param ...             The arguments to the note.
 */
void log_note( const s8 *spNote, ... ) {
    va_list vaArgs;
    s8      pBuffer[ MAX_LOG_MESSAGE_LENGTH ];

    va_start( vaArgs, spNote );
    vsnprintf( pBuffer, MAX_LOG_MESSAGE_LENGTH, spNote, vaArgs );
    va_end( vaArgs );

    fprintf( stderr, "note: %s", pBuffer );
}

/*
 *    Logs a warning to the console.
 *
 *    @param s8 *            The warning to log.
 *    @param ...             The arguments to the warning.
 */
void log_warn( const s8 *spWarning, ... ) {
    va_list vaArgs;
    s8      pBuffer[ MAX_LOG_MESSAGE_LENGTH ];

    va_start( vaArgs, spWarning );
    vsnprintf( pBuffer, MAX_LOG_MESSAGE_LENGTH, spWarning, vaArgs );
    va_end( vaArgs );

    fprintf( stderr, "warning: %s", pBuffer );
}

/*
 *    Logs an error to the console.
 *
 *    @param s8 *            The error to log.
 *    @param ...             The arguments to the error.
 */
void log_error( const s8 *spError, ... ) {
    va_list vaArgs;
    s8      pBuffer[ MAX_LOG_MESSAGE_LENGTH ];

    va_start( vaArgs, spError );
    vsnprintf( pBuffer, MAX_LOG_MESSAGE_LENGTH, spError, vaArgs );
    va_end( vaArgs );

    fprintf( stderr, "error: %s", pBuffer );
}

/*
 *    Logs a fatal error to the console.
 *
 *    @param s8 *            The fatal error to log.
 *    @param ...             The arguments to the fatal error.
 */
void log_fatal( const s8 *spFatal, ... ) {
    va_list vaArgs;
    s8      pBuffer[ MAX_LOG_MESSAGE_LENGTH ];

    va_start( vaArgs, spFatal );
    vsnprintf( pBuffer, MAX_LOG_MESSAGE_LENGTH, spFatal, vaArgs );
    va_end( vaArgs );

    fprintf( stderr, "fatal: %s", pBuffer );

    exit( EXIT_FAILURE );
}