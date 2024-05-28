/*
 *    lchikk_kompact.h    --    haeder for the Kompact file format.
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on May 27, 2024
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 * 
 *    This file declares the Kompact file format, used
 *    for storing key-value pairs in a compact format.
 */
#ifndef LCHIK_KOMPAKT_H
#define LCHIK_KOMPAKT_H

typedef struct {
    char *type;
    char *name;
    char *value;
} k_var_t;

typedef struct {
    k_var_t *vars;
    int      vars_len;
} k_ctx_t;

/*
 *    Returns a new k_ctx_t object.
 *
 *    @return   k_ctx_t    A new k_ctx_t object.
 */
k_ctx_t *k_ctx_new();

/*
 *    Reads a k file and modifies the k_ctx_t object.
 *
 *    @param    k_ctx_t   *ctx    The context to modify.
 *    @param    char      *path   The path to the k file.
 *
 *    @return   int               0 on success, -1 on failure.
 */
int k_ctx_read(k_ctx_t *ctx, char *path);

/*
 *    Writes a k_ctx_t object to a file with whitespace.
 *
 *    @param    k_ctx_t   *ctx    The context to write.
 *    @param    char      *path   The path to write to.
 * 
 *    @return   int               0 on success, -1 on failure.
 */
int k_ctx_write_ws(k_ctx_t *ctx, char *path, char *author);

/*
 *    Writes a k_ctx_t object to a file without whitespace.
 *
 *    @param    k_ctx_t   *ctx    The context to write.
 *    @param    char      *path   The path to write to.
 * 
 *    @return   int               0 on success, -1 on failure.
 */
int k_ctx_write(k_ctx_t *ctx, char *path);

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
int k_ctx_add(k_ctx_t *ctx, char *type, char *name, char *value);

/*
 *    Get a variable by name from a k_ctx_t object.
 *
 *    @param    k_ctx_t  *ctx     The context to get the variable from.
 *    @param    char     *name    The name of the variable.
 * 
 *    @return   k_var_t           The variable.
 */
k_var_t k_ctx_get(k_ctx_t *ctx, char *name);

/*
 *    Frees a k_ctx_t object.
 *
 *    @param    k_ctx_t    *ctx    The context to free.
 */
void k_ctx_free(k_ctx_t *ctx);

#endif /* LCHIK_KOMPAKT_H  */