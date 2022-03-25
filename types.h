/*
 *    types.h    --    header for general types
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 * 
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 * 
 *    Included here are the basic types used by the Chik engine.
 */
#pragma once

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

#if __unix__
    typedef __uint128_t u128;
#elif _WIN32
    /*
     *    Probably broken on windows.
     */
    typedef unsigned __int128 u128;
#else
    #error "Platform does not support 128-bit integers."
#endif /* __unix__  */

typedef char      s8;
typedef short     s16;
typedef int       s32;
typedef long long s64;

typedef float     f32;
typedef double    f64;

typedef void*     dl_handle_t;

typedef u128      handle_t;

typedef struct {
    f32 x;
    f32 y;
}chik_vec2_t;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
}chik_vec3_t;

typedef struct {
    chik_vec3_t aPos;
    u32         aColor;
//    chik_vec3_t aNormal;
    chik_vec2_t aTexCoord;
}vertex_t;