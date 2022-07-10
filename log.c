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

FILE *gpLogFile = nullptr;

/*
 *    Sets the color of the log messages.
 *
 *    @param log_color_e    The color to set.
 */
void log_set_color( log_color_e sColor ) {
    switch ( sColor ) {
        case LOG_COLOR_CLEAR:
            fprintf( stderr, "\033[0m" );
            break;
        case LOG_COLOR_BLACK:
            fprintf( stderr, "\033[30m" );
            break;
        case LOG_COLOR_RED:
            fprintf( stderr, "\033[31m" );
            break;
        case LOG_COLOR_GREEN:
            fprintf( stderr, "\033[32m" );
            break;
        case LOG_COLOR_YELLOW:
            fprintf( stderr, "\033[33m" );
            break;
        case LOG_COLOR_BLUE:
            fprintf( stderr, "\033[34m" );
            break;
        case LOG_COLOR_MAGENTA:
            fprintf( stderr, "\033[35m" );
            break;
        case LOG_COLOR_CYAN:
            fprintf( stderr, "\033[36m" );
            break;
        case LOG_COLOR_LIGHT_GREY:
            fprintf( stderr, "\033[37m" );
            break;
        case LOG_COLOR_DARK_GREY:
            fprintf( stderr, "\033[90m" );
            break;
        case LOG_COLOR_LIGHT_RED:
            fprintf( stderr, "\033[91m" );
            break;
        case LOG_COLOR_LIGHT_GREEN:
            fprintf( stderr, "\033[92m" );
            break;
        case LOG_COLOR_LIGHT_YELLOW:
            fprintf( stderr, "\033[93m" );
            break;
        case LOG_COLOR_LIGHT_BLUE:
            fprintf( stderr, "\033[94m" );
            break;
        case LOG_COLOR_LIGHT_MAGENTA:   
            fprintf( stderr, "\033[95m" );
            break;
        case LOG_COLOR_LIGHT_CYAN: 
            fprintf( stderr, "\033[96m" );
            break;
        case LOG_COLOR_WHITE:
            fprintf( stderr, "\033[97m" );
            break;
    }
}

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
    if ( gpLogFile ) {
        fprintf( gpLogFile, "%s", pBuffer );
    }
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
    log_set_color( LOG_COLOR_LIGHT_CYAN );
    vsnprintf( pBuffer, MAX_LOG_MESSAGE_LENGTH, spNote, vaArgs );
    va_end( vaArgs );

    fprintf( stderr, "note: %s", pBuffer );
    if ( gpLogFile ) {
        fprintf( gpLogFile, "note: %s", pBuffer );
    }
    log_set_color( LOG_COLOR_CLEAR );
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
    log_set_color( LOG_COLOR_MAGENTA );
    vsnprintf( pBuffer, MAX_LOG_MESSAGE_LENGTH, spWarning, vaArgs );
    va_end( vaArgs );

    fprintf( stderr, "warning: %s", pBuffer );
    if ( gpLogFile ) {
        fprintf( gpLogFile, "warning: %s", pBuffer );
    }
    log_set_color( LOG_COLOR_CLEAR );
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
    log_set_color( LOG_COLOR_LIGHT_RED );
    vsnprintf( pBuffer, MAX_LOG_MESSAGE_LENGTH, spError, vaArgs );
    va_end( vaArgs );

    fprintf( stderr, "error: %s", pBuffer );
    if ( gpLogFile ) {
        fprintf( gpLogFile, "error: %s", pBuffer );
    }
    log_set_color( LOG_COLOR_CLEAR );
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
    log_set_color( LOG_COLOR_LIGHT_RED );
    vsnprintf( pBuffer, MAX_LOG_MESSAGE_LENGTH, spFatal, vaArgs );
    va_end( vaArgs );

    fprintf( stderr, "fatal: %s", pBuffer );
    if ( gpLogFile ) {
        fprintf( gpLogFile, "fatal: %s", pBuffer );
    }
    log_set_color( LOG_COLOR_CLEAR );

    exit( EXIT_FAILURE );
}

/*
 *    Opens a file for logging.
 *
 *    @param s8 *            The file to open.
 */
void log_open_file( const s8 *spFile ) {
    gpLogFile = fopen( spFile, "w" );

    if ( gpLogFile == nullptr ) {
        log_warn( "void log_open_file( const s8 * ): Failed to open log file: %s", spFile );
    }
}

/*
 *    Closes the file opened for logging.
 */
void log_close_file( void ) {
    if ( gpLogFile != nullptr ) {
        fclose( gpLogFile );
    }
}