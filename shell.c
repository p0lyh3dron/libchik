/*
 *    shell.c    --    source for interacting with the engine via a shell
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on September 15, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file defines the functions for interacting with the
 *    engine via a shell.
 */
#include "shell.h"

#include <stdarg.h>
#include <string.h>

#include "log.h"

shell_command_t  _coms[LIBCHIK_SHELL_MAX_COMMANDS];
shell_variable_t _vars[LIBCHIK_SHELL_MAX_VARIABLES];

/*
 *    Displays the help text.
 */
void shell_help() {
    log_msg("\n\t- Welcome to Chishi, the shell for the Chik Engine!\n\n");
    log_msg("\t- To get started, you can type the name of a variable,\n");
    log_msg("\t  followed by a space, followed by a value,\n");
    log_msg("\t  to set the variable to that value. For example,\n");
    log_msg("\t 'fov 90' will set 'fov' to 90, if that variable name is "
            "registered.\n\n");
    log_msg(
        "\t- You can also type the name of a command, followed by a space,\n");
    log_msg("\t  followed by arguments, to run that command.\n");
    log_msg(
        "\t  For example, 'load_map test' will run the 'load_map' command,\n");
    log_msg("\t  if that command is registered.\n\n");
    log_msg("\t- To get a list of all registered commands, type 'commands'.\n");
    log_msg(
        "\t- To get a list of all registered variables, type 'variables'.\n");
    log_msg("\t- To get a list of all registered commands and variables, type "
            "'all'.\n");
    log_msg("\t- To see this message again, type 'help'.\n");
}

/*
 *    Displays a list of all registered commands.
 */
void shell_list_commands() {
    unsigned long i;

    log_msg("\n\t* Registered commands:\n\n");
    for (i = 0; i < LIBCHIK_SHELL_MAX_COMMANDS; i++) {
        if (_coms[i].name == nullptr) {
            break;
        }

        log_msg("\t\t- %s: '%s'\n", _coms[i].name, _coms[i].desc);
    }
}

/*
 *    Displays a list of all registered variables.
 */
void shell_list_variables() {
    unsigned long i;

    log_msg("\n\t* Registered variables:\n\n");
    for (i = 0; i < LIBCHIK_SHELL_MAX_VARIABLES; i++) {
        if (_vars[i].name == nullptr) {
            break;
        }

        log_msg("\t\t- %s: (set to %s) '%s'\n", _vars[i].name, _vars[i].val,
                _vars[i].desc);
    }
}

/*
 *    Displays a list of all registered commands and variables.
 */
void shell_list_all() {
    shell_list_commands();
    shell_list_variables();
}

/*
 *    Initializes the shell.
 */
void shell_init(void) {
    shell_command_t commands[] = {
        {"help", "Print the help message for the shell usage.", shell_help},
        {"commands", "List all registered commands.", shell_list_commands},
        {"variables", "List all registered variables.", shell_list_variables},
        {"all", "List all registered commands and variables.", shell_list_all},
        {nullptr, nullptr, nullptr}};

    memset(_coms, 0, sizeof(shell_command_t) * LIBCHIK_SHELL_MAX_COMMANDS);
    memset(_vars, 0, sizeof(shell_variable_t) * LIBCHIK_SHELL_MAX_VARIABLES);

    shell_register_commands(commands);
}

/*
 *    Registers shell commands.
 *
 *    @param shell_command_t *com   A shell command.
 */
void shell_register_commands(shell_command_t *com) {
    unsigned long i = 0;
    unsigned long j = 0;

    while (_coms[i].name != nullptr) {
        i++;
    }
    while (com[j].name != nullptr) {
        _coms[i++] = com[j];
        j++;
    }
}

/*
 *    Registers shell variables.
 *
 *    @param shell_variable_t *var   A shell variable.
 */
void shell_register_variables(shell_variable_t *var) {
    unsigned long i = 0;
    unsigned long j = 0;

    while (_vars[i].name != nullptr) {
        i++;
    }
    while (var[j].name != nullptr) {
        _vars[i++] = var[j];
        j++;
    }
}

/*
 *    Executes a shell command.
 *
 *    @param s8 *com    The command to execute.
 */
void shell_execute(s8 *com) {
    unsigned long i;
    s8            argv[LIBCHIK_SHELL_ARGV_MAX][LIBCHIK_SHELL_ARGV_SIZE] = {{0}};
    s64           argc                                                  = 0;
    char         *arg;

    /*
     *    Parse the command into arguments.
     */
    arg = strtok(com, " ");
    while (arg != nullptr) {
        strcpy(argv[argc], arg);
        argc++;
        arg = strtok(nullptr, " ");
    }

    /*
     *    Execute the command.
     */
    for (i = 0; i < LIBCHIK_SHELL_MAX_COMMANDS; i++) {
        if (_coms[i].name != nullptr) {
            if (strcmp(_coms[i].name, argv[0]) == 0) {
                log_msg("> %s\n", com);
                _coms[i].fun(argc, (s8 **)argv);
                return;
            }
        }
        if (_vars[i].name != nullptr) {
            if (strcmp(_vars[i].name, argv[0]) == 0) {
                log_msg("> %s\n", com);
                if (argc > 1) {
                    strcpy(_vars[i].val, argv[1]);
                    if (_vars[i].fun != nullptr) {
                        _vars[i].fun(argv[1]);
                    }
                }
                log_msg("\t- %s = %s\n", _vars[i].name, _vars[i].val);
                return;
            }
        }
    }

    VLOGF_WARN("Unknown command or variable: %s\n", argv[0]);

    return;
}

/*
 *    Gets a shell variable value.
 *
 *    @param s8 name    The name of the variable.
 *
 *    @return shell_val_u   The value of the variable.
 */
shell_val_u shell_get_variable(s8 *name) {
    unsigned long i;

    for (i = 0; i < LIBCHIK_SHELL_MAX_VARIABLES; i++) {
        if (_vars[i].name != nullptr) {
            if (strcmp(_vars[i].name, name) == 0) {
                switch (_vars[i].type) {
                case SHELL_VAR_INT:
                    return (shell_val_u){.i = atoi(_vars[i].val)};
                case SHELL_VAR_FLOAT:
                    return (shell_val_u){.f = atof(_vars[i].val)};
                case SHELL_VAR_STRING:
                    return (shell_val_u){.s = _vars[i].val};
                case SHELL_VAR_BOOL:
                    return (shell_val_u){
                        .b = (strcmp(_vars[i].val, "true") == 0)};
                }
            }
        }
    }
    return (shell_val_u){.i = 0};
}