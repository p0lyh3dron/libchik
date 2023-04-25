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

#define LIBCHIK_MAX_LOG_MESSAGE_LENGTH 1024

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

typedef enum {
    LIBCHIK_LOG_COLOR_CLEAR,
    LIBCHIK_LOG_COLOR_BLACK,
    LIBCHIK_LOG_COLOR_RED,
    LIBCHIK_LOG_COLOR_GREEN,
    LIBCHIK_LOG_COLOR_YELLOW,
    LIBCHIK_LOG_COLOR_BLUE,
    LIBCHIK_LOG_COLOR_MAGENTA,
    LIBCHIK_LOG_COLOR_CYAN,
    LIBCHIK_LOG_COLOR_LIGHT_GREY,
    LIBCHIK_LOG_COLOR_DARK_GREY,
    LIBCHIK_LOG_COLOR_LIGHT_RED,
    LIBCHIK_LOG_COLOR_LIGHT_GREEN,
    LIBCHIK_LOG_COLOR_LIGHT_YELLOW,
    LIBCHIK_LOG_COLOR_LIGHT_BLUE,
    LIBCHIK_LOG_COLOR_LIGHT_MAGENTA,
    LIBCHIK_LOG_COLOR_LIGHT_CYAN,
    LIBCHIK_LOG_COLOR_WHITE,
} log_color_e;

/*
 *    Sets the color of the log messages.
 *
 *    @param log_color_e color   The color to set.
 */
void log_set_color(log_color_e color);

/*
 *    Logs a message to the console.
 *
 *    @param char *message            The message to log.
 *    @param ...                    The arguments to the message.
 */
void log_msg(const char *message, ...);

/*
 *    Logs a note to the console.
 *
 *    @param char *note            The note to log.
 *    @param ...                 The arguments to the note.
 */
void log_note(const char *note, ...);

/*
 *    Logs a warning to the console.
 *
 *    @param char *warning            The warning to log.
 *    @param ...                    The arguments to the warning.
 */
void log_warn(const char *warning, ...);

/*
 *    Logs an error to the console.
 *
 *    @param char *error            The error to log.
 *    @param ...                  The arguments to the error.
 */
void log_error(const char *error, ...);

/*
 *    Logs a fatal error to the console.
 *
 *    @param char *fatal            The fatal error to log.
 *    @param ...                  The arguments to the fatal error.
 */
void log_fatal(const char *fatal, ...);

/*
 *    Opens a file for logging.
 *
 *    @param char *file            The file to open.
 */
void log_open_file(const char *file);
/*
 *    Closes the file opened for logging.
 */
void log_close_file(void);

#define VLOGF_MSG(msg, ...) log_msg("%s | " msg, __func__, __VA_ARGS__)
#define LOGF_MSG(msg)       log_msg("%s | " msg, __func__)

#define VLOGF_NOTE(note, ...) log_note("%s: " note, __func__, __VA_ARGS__)
#define LOGF_NOTE(note)       log_note("%s: " note, __func__)

#define VLOGF_WARN(warn, ...) log_warn("%s: " warn, __func__, __VA_ARGS__)
#define LOGF_WARN(warn)       log_warn("%s: " warn, __func__)

#define VLOGF_ERR(err, ...) log_error("%s: " err, __func__, __VA_ARGS__)
#define LOGF_ERR(err)       log_error("%s: " err, __func__)

#define VLOGF_FAT(fat, ...) log_msg("%s: " fat, __func__, __VA_ARGS__)
#define LOGF_FAT(fat)       log_msg("%s: " fat, __func__)
