/*
 *    shell.h    --    header for interacting with the engine via a shell
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on September 15, 2022
 * 
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 * 
 *    This file declares the shell interface functions. Engine modules
 *    as well as game code can create shell commands and variables.
 *    This allows the user to interact with the engine and game
 *    via strings which will be useful for debugging and testing.
 */
#ifndef LIBCHIK_SHELL_H
#define LIBCHIK_SHELL_H

#include "types.h"

#define LIBCHIK_SHELL_MAX_COMMANDS  256
#define LIBCHIK_SHELL_MAX_VARIABLES 256

#define LIBCHIK_SHELL_ARGV_MAX  32
#define LIBCHIK_SHELL_ARGV_SIZE 256

#define LIBCHIK_SHELL_VAR_VALUE_SIZE 256

typedef enum {
    SHELL_VAR_NONE,
    SHELL_VAR_INT,
    SHELL_VAR_FLOAT,
    SHELL_VAR_STRING,
    SHELL_VAR_BOOL
} shell_var_type_t;

typedef struct {
    s8     *apName;
    s8     *apDesc;
    void ( *apFunc )( s32 sArgc, s8 **spArgv );
} shell_command_t;

typedef struct {
    s8              *apName;
    s8              *apDesc;
    s8               apValue[ LIBCHIK_SHELL_VAR_VALUE_SIZE ];

    shell_var_type_t aType;
} shell_variable_t;

#define EXTERN_SHELL_COMMAND( name ) \
    extern shell_command_t name

#define EXTERN_SHELL_VARIABLE( name ) \
    extern shell_variable_t name

#define SHELL_COMMAND( name, desc, func ) \
    shell_command_t name = ( shell_command_t ){ .apName = #name, .apDesc = desc, .apFunc = func }

#define SHELL_VARIABLE( name, desc, value, type ) \
    shell_variable_t name = ( shell_variable_t ){ .apName = #name, .apDesc = desc, .apValue = value, .aType = type }

/*
 *    Initializes the shell.
 */
void shell_init( void );

/*
 *    Registers shell commands.
 *
 *    @param shell_command_t *   A shell command.
 */
void shell_register_commands( shell_command_t *spCommand );

/*
 *    Registers shell variables.
 *
 *    @param shell_variable_t *   A shell variable.
 */
void shell_register_variables( shell_variable_t *spVariable );

/*
 *    Executes a shell command.
 *
 *    @param s8*    The command to execute.
 */
void shell_execute( s8 *spCommand );

/*
 *    Gets a shell variable value.
 *
 *    @param s8*    The name of the variable.
 * 
 *    @return s8*   The value of the variable.
 */
s8 *shell_get_variable( s8 *spName );

#endif /* LIBCHIK_SHELL_H  */