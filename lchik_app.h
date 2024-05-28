/*
 *    lchik_app.h    --    header for application properties
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on April 14, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file declares all the functionality that describes the
 *    compiled application.
 */
#pragma once

#include "lchik_file.h"
#include "lchik_kompact.h"
#include "lchik_types.h"

typedef struct {
    const char *engine_name;
    vec3s_t     version;
} engineinfo_t;

typedef struct {
    const char *app_name;
    vec3s_t     version;
} appinfo_t;

extern watched_file_t _app_k;
extern k_ctx_t       *_app_ctx;

/*
 *    Initializes the app info.
 *
 *    @param const char * app_name       The application name.
 *    @param const vec3s_t version     The application version.
 */
void app_init(const char *app_name, const vec3s_t version);

/*
 *    Returns the app name.
 *
 *    @return const char *    The application name.
 */
const char *app_get_name(void);

/*
 *    Returns the app version.
 *
 *    @return vec3s_t    The application version.
 */
vec3s_t app_get_version(void);

/*
 *    Returns the engine name.
 *
 *    @return const char *    The engine name.
 */
const char *app_get_engine_name(void);

/*
 *    Returns the engine version.
 *
 *    @return vec3s_t    The engine version.
 */
vec3s_t app_get_engine_version(void);

/*
 *    Exits the app.
 */
void app_exit(void);