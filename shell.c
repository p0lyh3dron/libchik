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
 *    Registers shell commands.
 *
 *    @param shell_command_t    A shell command.
 *    @param ...                A list of shell commands.
 */
void shell_register_commands( shell_command_t sCommand, ... ) {
    va_list args;
    va_start( args, sCommand );

    s64 i = 0;
    while ( sCommand.apName != nullptr ) {
        gCommands[ i ] = sCommand;
        i++;
        sCommand = va_arg( args, shell_command_t );
    }

    va_end( args );
}

/*
 *    Registers shell variables.
 *
 *    @param shell_variable_t    A shell variable.
 *    @param ...                 A list of shell variables.
 */
void shell_register_variables( shell_variable_t sVariable, ... ) {
    va_list args;
    va_start( args, sVariable );

    s64 i = 0;
    while ( sVariable.apName != nullptr ) {
        gVariables[ i ] = sVariable;
        i++;
        sVariable = va_arg( args, shell_variable_t );
    }

    va_end( args );
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
    }
    
    log_warn( "Unknown command: %s\n", pArgv[ 0 ] );

    return;
}