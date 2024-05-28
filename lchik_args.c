/*
 *    lchik_args.c    --    source for argument parsing
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    Included here are the definitions for argument parsing.
 */
#include "lchik_args.h"

#include <stdlib.h>
#include <string.h>

#include "lchik_app.h"
#include "lchik_file.h"
#include "lchik_math.h"

int          _argc = 0;
const char **_argv = 0;

/*
 *    Initializes the argument parser.
 *
 *    @param const int argc        The number of arguments passed to the program.
 *    @param const char ** argv    The array of arguments passed to the program.
 */
void args_init(const int argc, const char **argv) {
    char buf[256] = {0};

    file_update(&_app_k);

    sprintf(buf, "%d", argc);
    k_ctx_add(_app_ctx, "u32", "argc", buf);
    k_ctx_add(_app_ctx, "u8[][]", "argv", str_list_to_str(argv, argc, "'n','n','n'"));

    k_ctx_write_ws(_app_ctx, _app_k.path, "Chik");

    _argc = argc;
    _argv = argv;
}

/*
 *    Returns if the argument is present.
 *
 *    @param  const char *arg     The argument to check for.
 *
 *    @return unsigned int              1 if the argument is present, 0 otherwise.
 */
unsigned int args_has(const char *arg) {
    file_update(&_app_k);

    int argc          = atoi(k_ctx_get(_app_ctx, "argc").value);
    const char **argv = str_to_str_list(k_ctx_get(_app_ctx, "argv").value, argc, "'n','n','n'");

    for (s64 i = 0; i < argc; i++) {
        if (strcmp(argv[i], arg) == 0) {
            for (s64 j = 0; j < argc; j++) free(argv[j]);

            free(argv);

            return 1;
        }
    }

    for (s64 j = 0; j < argc; j++) free(argv[j]);

    free(argv);

    return 0;
}

/*
 *    Returns the string value of the argument.
 *
 *    @param  const char *arg     The argument to check for.
 *
 *    @return const char *     The value of the argument, or NULL if it is not present.
 *
 */
const char *args_get_str(const char *arg) {
    static buf[256] = {0};
    file_update(&_app_k);

    int argc          = atoi(k_ctx_get(_app_ctx, "argc").value);
    const char **argv = str_to_str_list(k_ctx_get(_app_ctx, "argv").value, argc, "'n','n','n'");

    for (s64 i = 0; i < argc; i++) {
        if (strcmp(argv[i], arg) == 0) {
            strcpy(buf, argv[i + 1]);

            for (s64 j = 0; j < argc; j++) free(argv[j]);

            free(argv);

            return buf;
        }
    }
    
    for (s64 j = 0; j < argc; j++) free(argv[j]);

    free(argv);

    return (const char *)0x0;
}

/*
 *    Returns the integer value of the argument.
 *
 *    @param const char *arg     The argument to check for.
 *
 *    @return int             The value of the argument, or 0 if it is not
 * present.
 */
int args_get_int(const char *arg) {
    static buf[256] = {0};
    file_update(&_app_k);

    int argc          = atoi(k_ctx_get(_app_ctx, "argc").value);
    const char **argv = str_to_str_list(k_ctx_get(_app_ctx, "argv").value, argc, "'n','n','n'");

    for (s64 i = 0; i < argc; i++) {
        if (strcmp(argv[i], arg) == 0) {
            strcpy(buf, argv[i + 1]);

            for (s64 j = 0; j < argc; j++) free(argv[j]);

            free(argv);

            return atoi(buf);
        }
    }
    
    for (s64 j = 0; j < argc; j++) free(argv[j]);

    free(argv);

    return (const char *)0x0;
}

/*
 *    Returns the integer value of the argument.
 *
 *    @param const char *arg     The argument to check for.
 *
 *    @return float             The value of the argument, or 0.f if it is not
 * present.
 */
float args_get_float(const char* arg, float fallback) {
    
}

/*
 *    Returns the executable name.
 *
 *    @return const char *    The executable name.
 */
const char *args_get_executable(void) { return _argv[0]; }