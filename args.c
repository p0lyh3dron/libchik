/*
 *    args.c    --    source for argument parsing
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    Included here are the definitions for argument parsing.
 */
#include "args.h"

#include <stdlib.h>
#include <string.h>

int          _argc = 0;
const char **_argv = 0;

/*
 *    Initializes the argument parser.
 *
 *    @param const int argc        The number of arguments passed to the
 * program.
 *    @param const char ** argv    The array of arguments passed to the program.
 */
void args_init(const int argc, const char **argv) {
    _argc = argc;
    _argv = argv;
}

/*
 *    Returns if the argument is present.
 *
 *    @param  const char *arg     The argument to check for.
 *
 *    @return u32              1 if the argument is present, 0 otherwise.
 */
u32 args_has(const char *arg) {
    unsigned long i;

    for (i = 0; i < _argc; i++) {
        if (strcmp(_argv[i], arg) == 0) {
            return 1;
        }
    }

    return 0;
}

/*
 *    Returns the string value of the argument.
 *
 *    @param  const char *arg     The argument to check for.
 *
 *    @return const char *     The value of the argument, or NULL if it is not
 * present.
 *
 */
const char *args_get_str(const char *arg) {
    unsigned long i;

    for (i = 0; i < _argc; i++) {
        if (strcmp(_argv[i], arg) == 0) {
            return _argv[i + 1];
        }
    }

    return 0;
}

/*
 *    Returns the integer value of the argument.
 *
 *    @param const char *arg     The argument to check for.
 *
 *    @return s32             The value of the argument, or -1 if it is not
 * present.
 */
s32 args_get_int(const char *arg) {
    unsigned long i;

    for (i = 0; i < _argc; i++) {
        if (strcmp(_argv[i], arg) == 0) {
            return atoi(_argv[i + 1]);
        }
    }

    return -1;
}

/*
 *    Returns the executable name.
 *
 *    @return const char *    The executable name.
 */
const char *args_get_executable(void) { return _argv[0]; }