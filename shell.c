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

#include <string.h>
#include <stdarg.h>

#include "log.h"

shell_command_t  gCommands [ LIBCHIK_SHELL_MAX_COMMANDS  ];
shell_variable_t gVariables[ LIBCHIK_SHELL_MAX_VARIABLES ];

/*
 *    Displays the help text.
 */
void shell_help() {
    log_msg( "\n\t- Welcome to Chishi, the shell for the Chik Engine!\n\n" );
    log_msg( "\t- To get started, you can type the name of a variable,\n");
    log_msg( "\t  followed by a space, followed by a value,\n" );
    log_msg( "\t  to set the variable to that value. For example,\n" );
    log_msg( "\t 'fov 90' will set 'fov' to 90, if that variable name is registered.\n\n" );
    log_msg( "\t- You can also type the name of a command, followed by a space,\n");
    log_msg( "\t  followed by arguments, to run that command.\n" );
    log_msg( "\t  For example, 'load_map test' will run the 'load_map' command,\n");
    log_msg( "\t  if that command is registered.\n\n" );
    log_msg( "\t- To get a list of all registered commands, type 'commands'.\n" );
    log_msg( "\t- To get a list of all registered variables, type 'variables'.\n" );
    log_msg( "\t- To get a list of all registered commands and variables, type 'all'.\n" );
    log_msg( "\t- To see this message again, type 'help'.\n" );
}

/*
 *    Displays a list of all registered commands.
 */
void shell_list_commands() {
    log_msg( "\n\t* Registered commands:\n\n" );

    s64 i;
    for( i = 0; i < LIBCHIK_SHELL_MAX_COMMANDS; i++ ) {
        if( gCommands[ i ].apName == nullptr ) {
            break;
        }

        log_msg( "\t\t- %s: '%s'\n", gCommands[ i ].apName, gCommands[ i ].apDesc );
    }
}

/*
 *    Displays a list of all registered variables.
 */
void shell_list_variables() {
    log_msg( "\n\t* Registered variables:\n\n" );

    s64 i;
    for( i = 0; i < LIBCHIK_SHELL_MAX_VARIABLES; i++ ) {
        if( gVariables[ i ].apName == nullptr ) {
            break;
        }

        log_msg( "\t\t- %s: (set to %s) '%s'\n", gVariables[ i ].apName, gVariables[ i ].apValue, gVariables[ i ].apDesc );
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
void shell_init( void ) {
    memset( gCommands,  0, sizeof( shell_command_t  ) * LIBCHIK_SHELL_MAX_COMMANDS  );
    memset( gVariables, 0, sizeof( shell_variable_t ) * LIBCHIK_SHELL_MAX_VARIABLES );

    shell_command_t commands[] = {
        { "help", "Print the help message for the shell usage.", shell_help },
        { "commands", "List all registered commands.", shell_list_commands },
        { "variables", "List all registered variables.", shell_list_variables },
        { "all", "List all registered commands and variables.", shell_list_all },
        { nullptr, nullptr, nullptr }
    };

    shell_register_commands( commands );
}

/*
 *    Registers shell commands.
 *
 *    @param shell_command_t *   A shell command.
 */
void shell_register_commands( shell_command_t *spCommand ) {
    s64 i = 0;
    while ( gCommands[ i ].apName != nullptr ) {
        i++;
    }
    s64 j = 0;
    while ( spCommand[ j ].apName != nullptr ) {
        gCommands[ i++ ] = spCommand[ j ];
        j++;
    }
}

/*
 *    Registers shell variables.
 *
 *    @param shell_variable_t *   A shell variable.
 */
void shell_register_variables( shell_variable_t *spVariable ) {
    s64 i = 0;
    while ( gVariables[ i ].apName != nullptr ) {
        i++;
    }
    s64 j = 0;
    while ( spVariable[ j ].apName != nullptr ) {
        gVariables[ i++ ] = spVariable[ j ];
        j++;
    }
}

/*
 *    Executes a shell command.
 *
 *    @param s8*    The command to execute.
 */
void shell_execute( s8 *spCommand ) {
    s8  pArgv[ LIBCHIK_SHELL_ARGV_MAX ][ LIBCHIK_SHELL_ARGV_SIZE ] = { { 0 } };
    s64 argc = 0;

    /*
     *    Parse the command into arguments.
     */
    s8 *pArg = strtok( spCommand, " " );
    while ( pArg != nullptr ) {
        strcpy( pArgv[ argc ], pArg );
        argc++;
        pArg = strtok( nullptr, " " );
    }

    /*
     *    Execute the command.
     */
    s64 i;
    for ( i = 0; i < LIBCHIK_SHELL_MAX_COMMANDS; i++ ) {
        if ( gCommands[ i ].apName != nullptr ) {
            if ( strcmp( gCommands[ i ].apName, pArgv[ 0 ] ) == 0 ) {
                log_msg( "> %s\n", spCommand );
                gCommands[ i ].apFunc( argc, pArgv );
                return;
            }
        }
        if ( gVariables[ i ].apName != nullptr ) {
            if ( strcmp( gVariables[ i ].apName, pArgv[ 0 ] ) == 0 ) {
                log_msg( "> %s\n", spCommand );
                if ( argc > 1 ) {
                    strcpy( gVariables[ i ].apValue, pArgv[ 1 ] );
                }
                log_msg( "\t- %s = %s\n", gVariables[ i ].apName, gVariables[ i ].apValue );
                return;
            }
        }
    }
    
    log_warn( "Unknown command or variable: %s\n", pArgv[ 0 ] );

    return;
}

/*
 *    Gets a shell variable value.
 *
 *    @param s8*    The name of the variable.
 * 
 *    @return s8*   The value of the variable.
 */
s8 *shell_get_variable( s8 *spName ) {
    s64 i;
    for ( i = 0; i < LIBCHIK_SHELL_MAX_VARIABLES; i++ ) {
        if ( gVariables[ i ].apName != nullptr ) {
            if ( strcmp( gVariables[ i ].apName, spName ) == 0 ) {
                return gVariables[ i ].apValue;
            }
        }
    }
    return nullptr;
}