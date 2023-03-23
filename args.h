/*
 *    args.h    --    header for argument parsing
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    Included here is a simple interface for parsing command line
 *    arguments.
 */
#pragma once

#include "types.h"

/*
 *    Initializes the argument parser.
 *
 *    @param const int argc       The number of arguments passed to the program.
 *    @param const char **argv    The array of arguments passed to the program.
 */
void args_init(const int argc, const char **argv);

/*
 *    Returns if the argument is present.
 *
 *    @param  const char *arg     The argument to check for.
 *
 *    @return unsigned int              1 if the argument is present, 0 otherwise.
 */
unsigned int args_has(const char *arg);

/*
 *    Returns the string value of the argument.
 *
 *    @param  const char *arg     The argument to check for.
 *
 *    @return const char *     The value of the argument, or NULL if it is not
 * present.
 */
const char *args_get_str(const char *arg);

/*
 *    Returns the integer value of the argument.
 *
 *    @param const char *arg     The argument to check for.
 *
 *    @return int             The value of the argument, or -1 if it is not
 * present.
 */
int args_get_int(const char *arg);

/*
 *    Returns the executable name.
 *
 *    @return const char *    The executable name.
 */
const char *args_get_executable(void);