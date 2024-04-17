/*
 *    lchik_types.h    --    header for general types
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

#define CH_NULL (void *)0x0

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
#ifdef __unix__
typedef unsigned long      u64;
#elif _WIN32
typedef unsigned long long u64;
#endif /* __unix__  */

#define ARR_LEN(x) \
    ((sizeof(x) / sizeof(0 [x])) / ((unsigned long)(!(sizeof(x) % sizeof(0 [x])))))

#if __unix__
typedef __uint128_t u128;
#elif _WIN32
/*
 *    Probably broken on windows.
 */
#define DLL_EXPORT  __declspec(dllexport)
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

typedef char bool;

static unsigned int _pixel_sizes[2] = {
   3, /* IMAGE_FMT_RGB8   */
   4, /* IMAGE_FMT_RGBA8  */
};

typedef enum {
    IMAGE_FMT_RGB8  = 0,
    IMAGE_FMT_RGBA8 = 1,
} image_fmt_e;

typedef struct {
    unsigned int  index;
    unsigned int  magic;
    unsigned long size;
} trap_t;

typedef struct {
    float x;
    float y;
} vec2_t;

typedef struct {
    int x;
    int y;
} vec2u_t;

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

typedef struct {
    int x;
    int y;
    int z;
} vec3s_t;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} vec4_t;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} color32_t;

typedef union {
    vec2_t    v2;
    vec2u_t   v2u;
    vec3_t    v3;
    vec4_t    v4;
    color32_t c32;
} vec_t;

typedef struct {
    float v[16];
} mat4_t;

typedef struct {
    unsigned int   width;
    unsigned int   height;
    unsigned int   fmt;
    unsigned int   size;
    unsigned char *buf;
} image_t;

typedef struct {
    image_t *image;
} texture_t;

typedef struct {
    image_t* albedo;
    image_t* ambient_occlusion;
    image_t* emission;

    float    ambient_occlusion_power;
    float    emission_power;
} material_t;

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
 *    @return unsigned int           The size of the vertex component in bytes.
 */
unsigned int get_vertex_component_size(v_format_e sFmt);

typedef struct {
    color32_t color;
    vec2u_t   pos;
} fragment_t;

typedef enum {
    V_POS = 1 << 0,
} v_usage_e;

typedef struct {
    v_usage_e    usage;
    v_format_e   fmt;
    unsigned int stride;
    unsigned int offset;
} v_attrib_t;

typedef struct {
    v_attrib_t   attributes[MAX_VECTOR_ATTRIBUTES];
    unsigned int count;
    unsigned int stride;
    void (*f_fun)(fragment_t *, void *, void *, material_t *);
    void (*v_fun)(void *, void *, void *);
    void (*v_scale)(void *, void *, float);
    void (*v_add)(void *, void *, void *);
} v_layout_t;

typedef struct {
    vec3_t normal;
    float  dist;
} plane_t;

typedef struct {
    plane_t planes[6];
} frustum_t;