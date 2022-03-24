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

int          gNumArgs  = 0;
const char **gpArgv    = 0;

/*
 *    Initializes the argument parser.
 *
 *    @param const int        The number of arguments passed to the program.
 *    @param const char **    The array of arguments passed to the program.
 */
void args_init( const int sArgc, const char **spArgv ) {
    gNumArgs = sArgc;
    gpArgv   = spArgv;
}

/*
 *    Returns if the argument is present.
 *
 *    @param  const char *     The argument to check for.
 *
 *    @return u32              1 if the argument is present, 0 otherwise.
 */
u32 args_has( const char *spArg ) {
    int i;

    for( i = 0; i < gNumArgs; i++ ) {
        if( strcmp( gpArgv[ i ], spArg ) == 0 ) {
            return 1;
        }
    }

    return 0;
}

/*
 *    Returns the string value of the argument.
 *
 *    @param  const char *     The argument to check for.
 *
 *    @return const char *     The value of the argument, or NULL if it is not present.
 */
const char *args_get_str( const char *spArg ) {
    int i;

    for( i = 0; i < gNumArgs; i++ ) {
        if( strcmp( gpArgv[ i ], spArg ) == 0 ) {
            return gpArgv[ i + 1 ];
        }
    }

    return 0;
}

/*
 *    Returns the integer value of the argument.
 *
 *    @param const char *     The argument to check for.
 *
 *    @return s32             The value of the argument, or -1 if it is not present.
 */
s32 args_get_int( const char *spArg ) {
    int i;

    for( i = 0; i < gNumArgs; i++ ) {
        if( strcmp( gpArgv[ i ], spArg ) == 0 ) {
            return atoi( gpArgv[ i + 1 ] );
        }
    }

    return -1;
}

/*
 *    Returns the executable name.
 *
 *    @return const char *    The executable name.
 */
const char *args_get_executable( void ) {
    return gpArgv[ 0 ];
}