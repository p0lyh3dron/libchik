/*
 *    log.h    --    header for logging messages.
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 * 
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 * 
 *    Included here is a simple interface for logging messages.
 */
#pragma once

#pragma MESSAGE( "log.h" )

#define MAX_LOG_MESSAGE_LENGTH 1024

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

typedef enum {
    LOG_COLOR_CLEAR,
    LOG_COLOR_BLACK,
    LOG_COLOR_RED,
    LOG_COLOR_GREEN,
    LOG_COLOR_YELLOW,
    LOG_COLOR_BLUE,
    LOG_COLOR_MAGENTA,
    LOG_COLOR_CYAN,
    LOG_COLOR_LIGHT_GREY,
    LOG_COLOR_DARK_GREY,
    LOG_COLOR_LIGHT_RED,
    LOG_COLOR_LIGHT_GREEN,
    LOG_COLOR_LIGHT_YELLOW,
    LOG_COLOR_LIGHT_BLUE,
    LOG_COLOR_LIGHT_MAGENTA,
    LOG_COLOR_LIGHT_CYAN,
    LOG_COLOR_WHITE,
} log_color_e;

/*
 *    Sets the color of the log messages.
 *
 *    @param log_color_e    The color to set.
 */
void log_set_color( log_color_e sColor );

/*
 *    Logs a message to the console.
 *
 *    @param s8 *            The message to log.
 *    @param ...             The arguments to the message.
 */
void log_msg( const s8 *spMessage, ... );

/*
 *    Logs a note to the console.
 *
 *    @param s8 *            The note to log.
 *    @param ...             The arguments to the note.
 */
void log_note( const s8 *spNote, ... );

/*
 *    Logs a warning to the console.
 *
 *    @param s8 *            The warning to log.
 *    @param ...             The arguments to the warning.
 */
void log_warn( const s8 *spWarning, ... );

/*
 *    Logs an error to the console.
 *
 *    @param s8 *            The error to log.
 *    @param ...             The arguments to the error.
 */
void log_error( const s8 *spError, ... );

/*
 *    Logs a fatal error to the console.
 *
 *    @param s8 *            The fatal error to log.
 *    @param ...             The arguments to the fatal error.
 */
void log_fatal( const s8 *spFatal, ... );

/*
 *    Opens a file for logging.
 *
 *    @param s8 *            The file to open.
 */
void log_open_file( const s8 *spFile );

/*
 *    Closes the file opened for logging.
 */
void log_close_file( void );