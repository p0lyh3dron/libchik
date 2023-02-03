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

#define nullptr (void *)0

#define true  1
#define false 0

#define MAX_VECTOR_ATTRIBUTES 16

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

#define ARR_LEN(x)                                                             \
    ((sizeof(x) / sizeof(0 [x])) / ((u64)(!(sizeof(x) % sizeof(0 [x])))))

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

typedef float  f32;
typedef double f64;

typedef void *dl_handle_t;

typedef s8 bool;

typedef struct {
    u32 index;
    u32 magic;
    u64 size;
} trap_t;

typedef struct {
    f32 x;
    f32 y;
} vec2_t;

typedef struct {
    s32 x;
    s32 y;
} vec2u_t;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} vec3_t;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} vec3s_t;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} vec4_t;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} color32_t;

typedef union {
    vec2_t    v2;
    vec2u_t   v2u;
    vec3_t    v3;
    vec4_t    v4;
    color32_t c32;
} vec_t;

typedef struct {
    f32 v[16];
} mat4_t;

typedef struct {
    u32  width;
    u32  height;
    u32  fmt;
    u32  size;
    u32 *buf;
} image_t;

typedef struct {
    image_t *image;
} texture_t;

typedef enum {
    V_R8G8B8A8_U,
    V_R8G8B8A8_S,

    V_R32_U,
    V_R32G32_U,
    V_R32G32B32_U,
    V_R32G32B32A32_U,

    V_R32_F,
    V_R32G32_F,
    V_R32G32B32_F,
    V_R32G32B32A32_F,
} v_format_e;

/*
 *    Returns the size of a vertex component in bytes.
 *
 *    @param v_format_e     The vertex format.
 *
 *    @return u32           The size of the vertex component in bytes.
 */
u32 get_vertex_component_size(v_format_e sFmt);

typedef struct {
    color32_t color;
    vec2u_t   pos;
} fragment_t;

typedef enum {
    V_POS = 1 << 0,
} v_usage_e;

typedef struct {
    v_usage_e  usage;
    v_format_e fmt;
    u32        stride;
    u32        offset;
} v_attrib_t;

typedef struct {
    v_attrib_t attributes[MAX_VECTOR_ATTRIBUTES];
    u32        count;
    u32        stride;
    void (*fun)(fragment_t *, void *, void *);
} v_layout_t;

typedef struct {
    vec3_t normal;
    f32    dist;
} plane_t;

typedef struct {
    plane_t planes[6];
} frustum_t;