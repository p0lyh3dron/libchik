/*
 *    app.c    --    source for application properties
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on April 14, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file defines all the functionality that describes the
 *    compiled application.
 */
#include "app.h"

appinfo_t _app_info = {0};

const engineinfo_t _engine_info = {"Chik", {0, 0, 0}};

/*
 *    Initializes the app info.
 *
 *    @param const s8 * app_name       The application name.
 *    @param const vec3s_t version     The application version.
 */
void app_init(const s8 *app_name, const vec3s_t version) {
    _app_info.app_name = app_name;
    _app_info.version  = version;
}

/*
 *    Returns the app name.
 *
 *    @return const s8 *    The application name.
 */
const s8 *app_get_name(void) { return _app_info.app_name; }

/*
 *    Returns the app version.
 *
 *    @return vec3s_t    The application version.
 */
vec3s_t app_get_version(void) { return _app_info.version; }