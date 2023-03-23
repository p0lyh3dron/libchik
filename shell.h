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

typedef union {
    int   i;
    float f;
    char  s[LIBCHIK_SHELL_VAR_VALUE_SIZE];
    bool  b;
} shell_val_u;

typedef struct {
    char *name;
    char *desc;
    void (*fun)(int, char **);
} shell_command_t;

typedef struct {
    char *name;
    char *desc;
    char  val[LIBCHIK_SHELL_VAR_VALUE_SIZE];
    void (*fun)(char *);

    shell_var_type_t type;
} shell_variable_t;

#define EXTERN_SHELL_COMMAND(name) extern shell_command_t name

#define EXTERN_SHELL_VARIABLE(name) extern shell_variable_t name

#define SHELL_COMMAND(name, desc, func)          \
    shell_command_t name = (shell_command_t) {   \
        .name = #name, .desc = desc, .fun = func \
    }

#define SHELL_VARIABLE(name, desc, value, type)                   \
    shell_variable_t name = (shell_variable_t) {                  \
        .name = #name, .desc = desc, .value = value, .type = type \
    }

/*
 *    Displays the help text.
 */
void shell_help();

/*
 *    Displays a list of all registered commands.
 */
void shell_list_commands();

/*
 *    Displays a list of all registered variables.
 */
void shell_list_variables();

/*
 *    Displays a list of all registered commands and variables.
 */
void shell_list_all();

/*
 *    Initializes the shell.
 */
void shell_init(void);

/*
 *    Registers shell commands.
 *
 *    @param shell_command_t *com   A shell command.
 */
void shell_register_commands(shell_command_t *com);

/*
 *    Registers shell variables.
 *
 *    @param shell_variable_t *var   A shell variable.
 */
void shell_register_variables(shell_variable_t *var);

/*
 *    Executes a shell command.
 *
 *    @param char *com    The command to execute.
 */
void shell_execute(char *com);

/*
 *    Gets a shell variable value.
 *
 *    @param char name    The name of the variable.
 *
 *    @return shell_val_u   The value of the variable.
 */
shell_val_u shell_get_variable(char *name);

#endif /* LIBCHIK_SHELL_H  */