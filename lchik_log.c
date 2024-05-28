/*
 *    lchik_log.c    --    source for logging messages.
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    Included here are the definitions for logging messages.
 */
#include "lchik_log.h"

#include <stdarg.h>

/*
 *    Sets the color of the log messages.
 *
 *    @param log_color_e color   The color to set.
 */
void log_set_color(log_color_e color) {
    switch (color) {
    case LIBCHIK_LOG_COLOR_CLEAR:
        fprintf(stderr, "\033[0m");
        break;
    case LIBCHIK_LOG_COLOR_BLACK:
        fprintf(stderr, "\033[30m");
        break;
    case LIBCHIK_LOG_COLOR_RED:
        fprintf(stderr, "\033[31m");
        break;
    case LIBCHIK_LOG_COLOR_GREEN:
        fprintf(stderr, "\033[32m");
        break;
    case LIBCHIK_LOG_COLOR_YELLOW:
        fprintf(stderr, "\033[33m");
        break;
    case LIBCHIK_LOG_COLOR_BLUE:
        fprintf(stderr, "\033[34m");
        break;
    case LIBCHIK_LOG_COLOR_MAGENTA:
        fprintf(stderr, "\033[35m");
        break;
    case LIBCHIK_LOG_COLOR_CYAN:
        fprintf(stderr, "\033[36m");
        break;
    case LIBCHIK_LOG_COLOR_LIGHT_GREY:
        fprintf(stderr, "\033[37m");
        break;
    case LIBCHIK_LOG_COLOR_DARK_GREY:
        fprintf(stderr, "\033[90m");
        break;
    case LIBCHIK_LOG_COLOR_LIGHT_RED:
        fprintf(stderr, "\033[91m");
        break;
    case LIBCHIK_LOG_COLOR_LIGHT_GREEN:
        fprintf(stderr, "\033[92m");
        break;
    case LIBCHIK_LOG_COLOR_LIGHT_YELLOW:
        fprintf(stderr, "\033[93m");
        break;
    case LIBCHIK_LOG_COLOR_LIGHT_BLUE:
        fprintf(stderr, "\033[94m");
        break;
    case LIBCHIK_LOG_COLOR_LIGHT_MAGENTA:
        fprintf(stderr, "\033[95m");
        break;
    case LIBCHIK_LOG_COLOR_LIGHT_CYAN:
        fprintf(stderr, "\033[96m");
        break;
    case LIBCHIK_LOG_COLOR_WHITE:
        fprintf(stderr, "\033[97m");
        break;
    }
}

/*
 *    Logs a message to the console.
 *
 *    @param char *message            The message to log.
 *    @param ...                    The arguments to the message.
 */
void log_msg(const char *message, ...) {
    va_list args_va;
    char    buf[LIBCHIK_MAX_LOG_MESSAGE_LENGTH];

    va_start(args_va, message);
    vsnprintf(buf, LIBCHIK_MAX_LOG_MESSAGE_LENGTH, message, args_va);
    va_end(args_va);

    printf("%s", buf);
}

/*
 *    Logs a note to the console.
 *
 *    @param char *note            The note to log.
 *    @param ...                 The arguments to the note.
 */
void log_note(const char *note, ...) {
    va_list args_va;
    char    buf[LIBCHIK_MAX_LOG_MESSAGE_LENGTH];

    va_start(args_va, note);
    log_set_color(LIBCHIK_LOG_COLOR_LIGHT_CYAN);
    vsnprintf(buf, LIBCHIK_MAX_LOG_MESSAGE_LENGTH, note, args_va);
    va_end(args_va);

    fprintf(stderr, "note | ");
    log_set_color(LIBCHIK_LOG_COLOR_CLEAR);
    fprintf(stderr, "%s", buf);
}

/*
 *    Logs a warning to the console.
 *
 *    @param char *warning            The warning to log.
 *    @param ...                    The arguments to the warning.
 */
void log_warn(const char *warning, ...) {
    va_list args_va;
    char    buf[LIBCHIK_MAX_LOG_MESSAGE_LENGTH];

    va_start(args_va, warning);
    log_set_color(LIBCHIK_LOG_COLOR_MAGENTA);
    vsnprintf(buf, LIBCHIK_MAX_LOG_MESSAGE_LENGTH, warning, args_va);
    va_end(args_va);

    fprintf(stderr, "warning | ");
    log_set_color(LIBCHIK_LOG_COLOR_CLEAR);
    fprintf(stderr, "%s", buf);

}

/*
 *    Logs an error to the console.
 *
 *    @param char *error            The error to log.
 *    @param ...                  The arguments to the error.
 */
void log_error(const char *error, ...) {
    va_list args_va;
    char    buf[LIBCHIK_MAX_LOG_MESSAGE_LENGTH];

    va_start(args_va, error);
    log_set_color(LIBCHIK_LOG_COLOR_LIGHT_RED);
    vsnprintf(buf, LIBCHIK_MAX_LOG_MESSAGE_LENGTH, error, args_va);
    va_end(args_va);

    fprintf(stderr, "error | ");
    log_set_color(LIBCHIK_LOG_COLOR_CLEAR);
    fprintf(stderr, "%s", buf);
}

/*
 *    Logs a fatal error to the console.
 *
 *    @param char *fatal            The fatal error to log.
 *    @param ...                  The arguments to the fatal error.
 */
void log_fatal(const char *fatal, ...) {
    va_list args_va;
    char    buf[LIBCHIK_MAX_LOG_MESSAGE_LENGTH];

    va_start(args_va, fatal);
    log_set_color(LIBCHIK_LOG_COLOR_LIGHT_RED);
    vsnprintf(buf, LIBCHIK_MAX_LOG_MESSAGE_LENGTH, fatal, args_va);
    va_end(args_va);

    fprintf(stderr, "fatal | ");
    log_set_color(LIBCHIK_LOG_COLOR_CLEAR);
    fprintf(stderr, "%s", buf);

    exit(EXIT_FAILURE);
}