/*
 *    lchik_app.c    --    source for application properties
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on April 14, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file defines all the functionality that describes the
 *    compiled application.
 */
#include "lchik_app.h"

#include "lchik_file.h"
#include "lchik_kompact.h"
#include "lchik_math.h"

watched_file_t _app_k   = {0};
k_ctx_t       *_app_ctx = (k_ctx_t *)0x0;

const engineinfo_t _engine_info = {"Chik", {0, 0, 0}};

/*
 *    Returns the name of the appfile.
 *
 *    @return const char *    The name of the appfile.
 */
const char *app_get_appfile_name(void) { static char buf[256] = {0}; sprintf(buf, "app-%d.k", getpid()); return buf; }

/*
 *    Updates the app info.
 */
void app_update(void) {
    k_ctx_free(_app_ctx);
    _app_ctx = k_ctx_new();

    k_ctx_read(_app_ctx, _app_k.path);
}

/*
 *    Initializes the app info.
 *
 *    @param const char * app_name       The application name.
 *    @param const vec3s_t version     The application version.
 */
void app_init(const char *app_name, const vec3s_t version) {
    char buf[256] = {0};
    k_ctx_t *ctx  = k_ctx_new();

    k_ctx_read(ctx, app_get_appfile_name());

    sprintf(buf, "\"%s\"", _engine_info.engine_name);
    k_ctx_add(ctx, "u8[]", "engine_name", buf);
    k_ctx_add(ctx, "u32[]", "engine_version", vec3_i_to_str(_engine_info.version, "n,n,n"));
    sprintf(buf, "\"%s\"", app_name);
    k_ctx_add(ctx, "u8[]", "app_name", buf);
    k_ctx_add(ctx, "u32[]", "app_version", vec3_i_to_str(version, "n,n,n"));

    k_ctx_write_ws(ctx, app_get_appfile_name(), "Chik");

    _app_ctx = ctx;
    
    file_create(&_app_k, app_get_appfile_name(), app_update);
}

/*
 *    Returns the app name.
 *
 *    @return const char *    The application name.
 */
const char *app_get_name(void) {
    file_update(&_app_k);

    return k_ctx_get(_app_ctx, "app_name").value;
}

/*
 *    Returns the app version.
 *
 *    @return vec3s_t    The application version.
 */
vec3s_t app_get_version(void) { 
    file_update(&_app_k);

    return str_to_vec3_i(k_ctx_get(_app_ctx, "app_version").value, "n,n,n"); 
}

/*
 *    Returns the engine name.
 *
 *    @return const char *    The engine name.
 */
const char *app_get_engine_name(void) { return _engine_info.engine_name; }

/*
 *    Returns the engine version.
 *
 *    @return vec3s_t    The engine version.
 */
vec3s_t app_get_engine_version(void) { return _engine_info.version; }

/*
 *    Exits the app.
 */
void app_exit(void) {
    k_ctx_free(_app_ctx);
    
    file_delete(_app_k.path);
}