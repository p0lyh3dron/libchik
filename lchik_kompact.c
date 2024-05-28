/*
 *    lchikk_kompact.c    --    source for the Kompact file format.
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on May 27, 2024
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 * 
 *    This file defines the Kompact file format, used
 *    for storing key-value pairs in a compact format.
 */
#include "lchik_kompact.h"

#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <memory.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/*
 *    Skips whitespace characters in a string.
 *
 *    @param    char    *str    The string to skip whitespace in.
 *    @param    int      i      The index to start at.
 *    @param    int      len    The length of the string.
 *
 *    @return   int              The new index.
 */
int skip_whitespace(char *str, int i, int len) {
    while ((i < len) && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')) {
        i++;
    }

    return i;
}

/*
 *    Returns a new k_ctx_t object.
 *
 *    @return   k_ctx_t    A new k_ctx_t object.
 */
k_ctx_t *k_ctx_new() {
    k_ctx_t *ctx = malloc(sizeof(k_ctx_t));

    ctx->vars     = (k_var_t *)0x0;
    ctx->vars_len = 0;

    return ctx;
}

/*
 *    Reads a k file and modifies the k_ctx_t object.
 *
 *    @param    k_ctx_t   *ctx    The context to modify.
 *    @param    char      *path   The path to the k file.
 *
 *    @return   int               0 on success, -1 on failure.
 */
int k_ctx_read(k_ctx_t *ctx, char *path) {
    int   fd  = open(path, O_RDONLY);
    char *buf = (char *)0x0;
    int   i   = 0;
    int   j   = 0;
    int   len = 0;

    if (fd < 0) {
        return -1;
    }

    len = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    buf = malloc(len);
    read(fd, buf, len);

    close(fd);

    i = skip_whitespace(buf, i, len);

    do {
        /* Skip comments, blocked by '$'.  */
        if (buf[i] == '$') {
            do {
                i++;
            } while (buf[i] != '$' && i < len);

            i++;

            continue;
        }

        ctx->vars = realloc(ctx->vars, (ctx->vars_len + 1) * sizeof(k_var_t));

        /* Parse type.  */
        j = i;
        do {
            i++;
        } while (buf[i] != ':' && buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n' && i < len);

        ctx->vars[ctx->vars_len].type = calloc(i - j + 1, 1);
        memcpy(ctx->vars[ctx->vars_len].type, buf + j, i - j);

        i = skip_whitespace(buf, i, len);
        i++;
        i = skip_whitespace(buf, i, len);

        /* Parse name.  */
        j = i;
        do {
            i++;
        } while (buf[i] != '=' && buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n' && i < len);

        ctx->vars[ctx->vars_len].name = calloc(i - j + 1, 1);
        memcpy(ctx->vars[ctx->vars_len].name, buf + j, i - j);

        i = skip_whitespace(buf, i, len);

        /* Parse value.  */
        if (buf[i] == '=') {
            i++;

            i = skip_whitespace(buf, i, len);

            j = i;

            /* Parse string.  */
            if (buf[i] == '"') {
                do {
                    i++;
                } while (buf[i] != '"' && i < len);
                i++;

                ctx->vars[ctx->vars_len].value = calloc(i - j + 1, 1);
                memcpy(ctx->vars[ctx->vars_len].value, buf + j, i - j);

                ctx->vars_len++;

                i = skip_whitespace(buf, i, len);
                i++;

                continue;
            }

            do {
                i++;
            } while (buf[i] != ';' && buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n' && i < len);

            ctx->vars[ctx->vars_len].value = calloc(i - j + 1, 1);
            memcpy(ctx->vars[ctx->vars_len].value, buf + j, i - j);

            ctx->vars_len++;

            i = skip_whitespace(buf, i, len);
            i++;
            i = skip_whitespace(buf, i, len);

            continue;
        }

        if (buf[i] == ';') {
            ctx->vars[ctx->vars_len].value = (char *)0x0;
            ctx->vars_len++;

            continue;
        }

        i = skip_whitespace(buf, i, len);
    } while (i < len);

    return 0;
}

/*
 *    Writes a k_ctx_t object to a file with whitespace.
 *
 *    @param    k_ctx_t   *ctx    The context to write.
 *    @param    char      *path   The path to write to.
 * 
 *    @return   int               0 on success, -1 on failure.
 */
int k_ctx_write_ws(k_ctx_t *ctx, char *path, char *author) {
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }

    time_t t = time((time_t *)0x0);

    write(fd, "$\n", 2);
    write(fd, "*    ", 5); write(fd, path, strlen(path)); write(fd, "    --    written by compact\n", 29);
    write(fd, "*\n", 2);
    write(fd, "*    Authored by ", 17); write(fd, author, strlen(author)); write(fd, " on ", 4); write(fd, ctime(&t), 24); write(fd, "\n", 1);
    write(fd, "$\n", 2);


    for (int i = 0; i < ctx->vars_len; i++) {
        write(fd, ctx->vars[i].type, strlen(ctx->vars[i].type));
        write(fd, ": ", 2);
        write(fd, ctx->vars[i].name, strlen(ctx->vars[i].name));

        if (ctx->vars[i].value != (char *)0x0) {
            write(fd, " = ", 3);
            write(fd, ctx->vars[i].value, strlen(ctx->vars[i].value));
        }

        write(fd, ";\n", 2);
    }

    close(fd);

    return 0;
}

/*
 *    Writes a k_ctx_t object to a file without whitespace.
 *
 *    @param    k_ctx_t   *ctx    The context to write.
 *    @param    char      *path   The path to write to.
 * 
 *    @return   int               0 on success, -1 on failure.
 */
int k_ctx_write(k_ctx_t *ctx, char *path) {
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        return -1;
    }

    for (int i = 0; i < ctx->vars_len; i++) {
        write(fd, ctx->vars[i].type, strlen(ctx->vars[i].type));
        write(fd, ":", 1);
        write(fd, ctx->vars[i].name, strlen(ctx->vars[i].name));

        if (ctx->vars[i].value != (char *)0x0) {
            write(fd, "=", 1);
            write(fd, ctx->vars[i].value, strlen(ctx->vars[i].value));
        }

        write(fd, ";", 1);
    }

    close(fd);

    return 0;
}

/*
 *    Add a variable to a k_ctx_t object.
 *
 *    @param    k_ctx_t  *ctx     The context to add the variable to.
 *    @param    char     *type    The type of the variable.
 *    @param    char     *name    The name of the variable.
 *    @param    char     *value   The value of the variable.
 *
 *    @return   int               0 on success, -1 on failure.
 */
int k_ctx_add(k_ctx_t *ctx, char *type, char *name, char *value) {
    ctx->vars = realloc(ctx->vars, (ctx->vars_len + 1) * sizeof(k_var_t));

    ctx->vars[ctx->vars_len].type  = strdup(type);
    ctx->vars[ctx->vars_len].name  = strdup(name);
    ctx->vars[ctx->vars_len].value = strdup(value);

    ctx->vars_len++;

    return 0;
}

/*
 *    Get a variable by name from a k_ctx_t object.
 *
 *    @param    k_ctx_t  *ctx     The context to get the variable from.
 *    @param    char     *name    The name of the variable.
 * 
 *    @return   k_var_t           The variable.
 */
k_var_t k_ctx_get(k_ctx_t *ctx, char *name) {
    for (int i = 0; i < ctx->vars_len; i++) {
        if (strcmp(ctx->vars[i].name, name) == 0) {
            return ctx->vars[i];
        }
    }

    k_var_t var = {0x0, 0x0, 0x0};

    return var;
}

/*
 *    Frees a k_ctx_t object.
 *
 *    @param    k_ctx_t    *ctx    The context to free.
 */
void k_ctx_free(k_ctx_t *ctx) {
    for (int i = 0; i < ctx->vars_len; i++) {
        free(ctx->vars[i].type);
        free(ctx->vars[i].name);
        free(ctx->vars[i].value);
    }

    free(ctx->vars);
    free(ctx);
}