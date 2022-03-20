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
 *    @param const int        The number of arguments passed to the program.
 *    @param const char **    The array of arguments passed to the program.
 */
void args_init( const int sArgc, const char **spArgv );

/*
 *    Returns if the argument is present.
 *
 *    @param  const char *     The argument to check for.
 *
 *    @return u32              1 if the argument is present, 0 otherwise.
 */
u32 args_has( const char *spArg );

/*
 *    Returns the string value of the argument.
 *
 *    @param  const char *     The argument to check for.
 *
 *    @return const char *     The value of the argument, or NULL if it is not present.
 */
const char *args_get_str( const char *spArg );

/*
 *    Returns the integer value of the argument.
 *
 *    @param const char *     The argument to check for.
 *
 *    @return s32             The value of the argument, or -1 if it is not present.
 */
s32 args_get_int( const char *spArg );