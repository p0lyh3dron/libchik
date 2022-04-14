/*
 *    app.h    --    header for application properties
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

#define APP_MAX_NAME_LEN 256

#include "types.h"

typedef struct {
    s8     *apAppName;
    vec3s_t aVersion;
} appinfo_t;

/*
 *    Initializes the app info.
 *
 *    @param const s8 *       The application name.
 *    @param vec3s_t          The application version.
 */
void app_init( const s8 *spAppName, const vec3s_t sVersion );

/*
 *    Returns the app name.
 *
 *    @return s8 *    The application name.
 */
s8 *app_get_name( void );

/*
 *    Returns the app version.
 *
 *    @return vec3s_t    The application version.
 */
vec3s_t app_get_version( void );