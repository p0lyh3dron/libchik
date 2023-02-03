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

FILE *_log_file = nullptr;

/*
 *    Sets the color of the log messages.
 *
 *    @param log_color_e color   The color to set.
 */
void log_set_color(log_color_e color) {
    switch (color) {
    case LOG_COLOR_CLEAR:
        fprintf(stderr, "\033[0m");
        break;
    case LOG_COLOR_BLACK:
        fprintf(stderr, "\033[30m");
        break;
    case LOG_COLOR_RED:
        fprintf(stderr, "\033[31m");
        break;
    case LOG_COLOR_GREEN:
        fprintf(stderr, "\033[32m");
        break;
    case LOG_COLOR_YELLOW:
        fprintf(stderr, "\033[33m");
        break;
    case LOG_COLOR_BLUE:
        fprintf(stderr, "\033[34m");
        break;
    case LOG_COLOR_MAGENTA:
        fprintf(stderr, "\033[35m");
        break;
    case LOG_COLOR_CYAN:
        fprintf(stderr, "\033[36m");
        break;
    case LOG_COLOR_LIGHT_GREY:
        fprintf(stderr, "\033[37m");
        break;
    case LOG_COLOR_DARK_GREY:
        fprintf(stderr, "\033[90m");
        break;
    case LOG_COLOR_LIGHT_RED:
        fprintf(stderr, "\033[91m");
        break;
    case LOG_COLOR_LIGHT_GREEN:
        fprintf(stderr, "\033[92m");
        break;
    case LOG_COLOR_LIGHT_YELLOW:
        fprintf(stderr, "\033[93m");
        break;
    case LOG_COLOR_LIGHT_BLUE:
        fprintf(stderr, "\033[94m");
        break;
    case LOG_COLOR_LIGHT_MAGENTA:
        fprintf(stderr, "\033[95m");
        break;
    case LOG_COLOR_LIGHT_CYAN:
        fprintf(stderr, "\033[96m");
        break;
    case LOG_COLOR_WHITE:
        fprintf(stderr, "\033[97m");
        break;
    }
}

/*
 *    Logs a message to the console.
 *
 *    @param s8 *message            The message to log.
 *    @param ...                    The arguments to the message.
 */
void log_msg(const s8 *message, ...) {
    va_list args_va;
    s8      buf[MAX_LOG_MESSAGE_LENGTH];

    va_start(args_va, message);
    vsnprintf(buf, MAX_LOG_MESSAGE_LENGTH, message, args_va);
    va_end(args_va);

    printf("%s", buf);
    if (_log_file) {
        fprintf(_log_file, "%s", buf);
    }
}

/*
 *    Logs a note to the console.
 *
 *    @param s8 *note            The note to log.
 *    @param ...                 The arguments to the note.
 */
void log_note(const s8 *note, ...) {
    va_list args_va;
    s8      buf[MAX_LOG_MESSAGE_LENGTH];

    va_start(args_va, note);
    log_set_color(LOG_COLOR_LIGHT_CYAN);
    vsnprintf(buf, MAX_LOG_MESSAGE_LENGTH, note, args_va);
    va_end(args_va);

    fprintf(stderr, "note | %s", buf);
    if (_log_file) {
        fprintf(_log_file, "note | %s", buf);
    }
    log_set_color(LOG_COLOR_CLEAR);
}

/*
 *    Logs a warning to the console.
 *
 *    @param s8 *warning            The warning to log.
 *    @param ...                    The arguments to the warning.
 */
void log_warn(const s8 *warning, ...) {
    va_list args_va;
    s8      buf[MAX_LOG_MESSAGE_LENGTH];

    va_start(args_va, warning);
    log_set_color(LOG_COLOR_MAGENTA);
    vsnprintf(buf, MAX_LOG_MESSAGE_LENGTH, warning, args_va);
    va_end(args_va);

    fprintf(stderr, "warning | %s", buf);
    if (_log_file) {
        fprintf(_log_file, "warning | %s", buf);
    }
    log_set_color(LOG_COLOR_CLEAR);
}

/*
 *    Logs an error to the console.
 *
 *    @param s8 *error            The error to log.
 *    @param ...                  The arguments to the error.
 */
void log_error(const s8 *error, ...) {
    va_list args_va;
    s8      buf[MAX_LOG_MESSAGE_LENGTH];

    va_start(args_va, error);
    log_set_color(LOG_COLOR_LIGHT_RED);
    vsnprintf(buf, MAX_LOG_MESSAGE_LENGTH, error, args_va);
    va_end(args_va);

    fprintf(stderr, "error | %s", buf);
    if (_log_file) {
        fprintf(_log_file, "error | %s", buf);
    }
    log_set_color(LOG_COLOR_CLEAR);
}

/*
 *    Logs a fatal error to the console.
 *
 *    @param s8 *fatal            The fatal error to log.
 *    @param ...                  The arguments to the fatal error.
 */
void log_fatal(const s8 *fatal, ...) {
    va_list args_va;
    s8      buf[MAX_LOG_MESSAGE_LENGTH];

    va_start(args_va, fatal);
    log_set_color(LOG_COLOR_LIGHT_RED);
    vsnprintf(buf, MAX_LOG_MESSAGE_LENGTH, fatal, args_va);
    va_end(args_va);

    fprintf(stderr, "fatal | %s", buf);
    if (_log_file) {
        fprintf(_log_file, "fatal | %s", buf);
    }
    log_set_color(LOG_COLOR_CLEAR);

    exit(EXIT_FAILURE);
}

/*
 *    Opens a file for logging.
 *
 *    @param s8 *file            The file to open.
 */
void log_open_file(const s8 *file) {
    _log_file = fopen(file, "w");

    if (_log_file == nullptr)
        VLOGF_WARN("Failed to open log file: %s", file);
}

/*
 *    Closes the file opened for logging.
 */
void log_close_file(void) {
    if (_log_file != nullptr) {
        fclose(_log_file);
    }
}