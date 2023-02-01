/*
 *    math.c    --    math operations
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 25, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file defines the functions used for math operations.
 */
#include "math.h"

//#if defined( __unix__ ) && ( __i386__ )
#if 1
#include <xmmintrin.h>
#elif defined(_WIN32) && (_M_X86)
#include <intrin.h>
#endif /* __unix__  */

/*
 *    Returns a 4x4 identity matrix.
 *
 *    @return mat4_t    The identity matrix.
 */
mat4_t m4_identity(void) {
    mat4_t sMat = {{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}};
    return sMat;
}

/*
 *    Multiply vec4_t by mat4_t.
 *
 *    @param  vec4_t vec    The vector to multiply.
 *    @param  mat4_t mat    The matrix to multiply.
 *
 *    @return mat4_t    The resulting matrix.
 */
mat4_t v4_mul_m4(vec4_t vec, mat4_t mat) {
    mat4_t m;

    /*
     *    Extend the vector to a 4x1 matrix.
     */

    return m;
}

/*
 *   Multiply mat4_t by vec4_t.
 *
 *    @param  mat4_t mat    The matrix to multiply.
 *    @param  vec4_t vec    The vector to multiply.
 *
 *    @return mat4_t    The resulting matrix.
 */
mat4_t m4_mul_v4(mat4_t mat, vec4_t vec) {

    mat4_t m = {vec.x, 0, 0, 0, vec.y, 0, 0, 0,
                vec.z, 0, 0, 0, vec.w, 0, 0, 0};

    return m4_mul_m4(mat, m);
}

/*
 *    Multiply mat4_t by mat4_t.
 *
 *    @param  mat4_t mat1    The matrix to multiply.
 *    @param  mat4_t mat2    The matrix to multiply.
 *
 *    @return mat4_t    The resulting matrix.
 */
mat4_t m4_mul_m4(mat4_t mat1, mat4_t mat2) {
    unsigned long i;
    mat4_t m;
//#if defined( __unix__ ) && defined( __i386__ ) || defined( _WIN32 ) && (
//_M_X86 )
#if 1
    __m128 r0 = _mm_load_ps(&mat2.v[0]);
    __m128 r1 = _mm_load_ps(&mat2.v[4]);
    __m128 r2 = _mm_load_ps(&mat2.v[8]);
    __m128 r3 = _mm_load_ps(&mat2.v[12]);

    for (i = 0; i < 4; ++i) {
        __m128 r0_ = _mm_set1_ps(mat1.v[i * 4 + 0]);
        __m128 r1_ = _mm_set1_ps(mat1.v[i * 4 + 1]);
        __m128 r2_ = _mm_set1_ps(mat1.v[i * 4 + 2]);
        __m128 r3_ = _mm_set1_ps(mat1.v[i * 4 + 3]);

        __m128 r =
            _mm_add_ps(_mm_add_ps(_mm_mul_ps(r0_, r0), _mm_mul_ps(r1_, r1)),
                       _mm_add_ps(_mm_mul_ps(r2_, r2), _mm_mul_ps(r3_, r3)));

        _mm_store_ps(&m.v[i * 4 + 0], r);
    }
#else
    m = (mat4_t){
        sMat1.v[0] * sMat2.v[0] + sMat1.v[1] * sMat2.v[4] +
            sMat1.v[2] * sMat2.v[8] + sMat1.v[3] * sMat2.v[12],
        sMat1.v[0] * sMat2.v[1] + sMat1.v[1] * sMat2.v[5] +
            sMat1.v[2] * sMat2.v[9] + sMat1.v[3] * sMat2.v[13],
        sMat1.v[0] * sMat2.v[2] + sMat1.v[1] * sMat2.v[6] +
            sMat1.v[2] * sMat2.v[10] + sMat1.v[3] * sMat2.v[14],
        sMat1.v[0] * sMat2.v[3] + sMat1.v[1] * sMat2.v[7] +
            sMat1.v[2] * sMat2.v[11] + sMat1.v[3] * sMat2.v[15],

        sMat1.v[4] * sMat2.v[0] + sMat1.v[5] * sMat2.v[4] +
            sMat1.v[6] * sMat2.v[8] + sMat1.v[7] * sMat2.v[12],
        sMat1.v[4] * sMat2.v[1] + sMat1.v[5] * sMat2.v[5] +
            sMat1.v[6] * sMat2.v[9] + sMat1.v[7] * sMat2.v[13],
        sMat1.v[4] * sMat2.v[2] + sMat1.v[5] * sMat2.v[6] +
            sMat1.v[6] * sMat2.v[10] + sMat1.v[7] * sMat2.v[14],
        sMat1.v[4] * sMat2.v[3] + sMat1.v[5] * sMat2.v[7] +
            sMat1.v[6] * sMat2.v[11] + sMat1.v[7] * sMat2.v[15],

        sMat1.v[8] * sMat2.v[0] + sMat1.v[9] * sMat2.v[4] +
            sMat1.v[10] * sMat2.v[8] + sMat1.v[11] * sMat2.v[12],
        sMat1.v[8] * sMat2.v[1] + sMat1.v[9] * sMat2.v[5] +
            sMat1.v[10] * sMat2.v[9] + sMat1.v[11] * sMat2.v[13],
        sMat1.v[8] * sMat2.v[2] + sMat1.v[9] * sMat2.v[6] +
            sMat1.v[10] * sMat2.v[10] + sMat1.v[11] * sMat2.v[14],
        sMat1.v[8] * sMat2.v[3] + sMat1.v[9] * sMat2.v[7] +
            sMat1.v[10] * sMat2.v[11] + sMat1.v[11] * sMat2.v[15],

        sMat1.v[12] * sMat2.v[0] + sMat1.v[13] * sMat2.v[4] +
            sMat1.v[14] * sMat2.v[8] + sMat1.v[15] * sMat2.v[12],
        sMat1.v[12] * sMat2.v[1] + sMat1.v[13] * sMat2.v[5] +
            sMat1.v[14] * sMat2.v[9] + sMat1.v[15] * sMat2.v[13],
        sMat1.v[12] * sMat2.v[2] + sMat1.v[13] * sMat2.v[6] +
            sMat1.v[14] * sMat2.v[10] + sMat1.v[15] * sMat2.v[14],
        sMat1.v[12] * sMat2.v[3] + sMat1.v[13] * sMat2.v[7] +
            sMat1.v[14] * sMat2.v[11] + sMat1.v[15] * sMat2.v[15],
    };
#endif /* __unix__ && __i386__ || _WIN32 && _M_X86  */
    return m;
}

/*
 *    Generate a rotation matrix.
 *
 *    @param  f32 ang     The angle to rotate by.
 *    @param  vec3_t axis The axis to rotate around.
 *
 *    @return mat4_t The resulting matrix.
 */
mat4_t m4_rotate(f32 ang, vec3_t axis) {
    if (axis.x == 0.0f && axis.y == 0.0f && axis.z == 0.0f) {
        return m4_identity();
    }
    /*
     *    TODO: Implement rotation about an arbitrary axis.
     */
    if (axis.x != 0.0f) {
        mat4_t m = {{1, 0, 0, 0, 0, cosf(ang), -sinf(ang), 0, 0,
                     sinf(ang), cosf(ang), 0, 0, 0, 0, 1}};
        return m;
    }
    if (axis.y != 0.0f) {
        mat4_t m = {{cosf(ang), 0, sinf(ang), 0, 0, 1, 0, 0,
                     -sinf(ang), 0, cosf(ang), 0, 0, 0, 0, 1}};
        return m;
    }
    if (axis.z != 0.0f) {
        mat4_t m = {{cosf(ang), -sinf(ang), 0, 0, sinf(ang),
                     cosf(ang), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}};
        return m;
    }
    return m4_identity();
}

/*
 *    Generate a translation matrix.
 *
 *    @param  vec3_t vec The translation vector.
 *
 *    @return mat4_t The resulting matrix.
 */
mat4_t m4_translate(vec3_t vec) {
    mat4_t m = {
        {1, 0, 0, vec.x, 0, 1, 0, vec.y, 0, 0, 1, vec.z, 0, 0, 0, 1}};
    return m;
}

/*
 *    Interpolates a vec2.
 *
 *    @param vec2_t *a    The return vector.
 *    @param vec2_t *b    The first vector.
 *    @param vec2_t *c    The differential.
 *    @param f32 step     The step.
 *
 *    @return u32        The return code.
 */
u32 vec2_interp(vec2_t *a, vec2_t *b, vec2_t *c, f32 step) {
    a->x = b->x * (1 - step) + c->x * step;
    a->y = b->y * (1 - step) + c->y * step;

    return 1;
}

/*
 *    Scales a vec2.
 *
 *    @param vec2_t *a    The return vector.
 *    @param vec2_t *b    The vector to scale.
 *    @param f32 scale    The scale.
 *
 *    @return u32        The return code.
 */
u32 vec2_scale(vec2_t *a, vec2_t *b, f32 scale) {
    a->x = b->x * scale;
    a->y = b->y * scale;

    return 1;
}

/*
 *    Interpolates a vec2u.
 *
 *    @param vec2u_t *a    The return vector.
 *    @param vec2u_t *b    The first vector.
 *    @param vec2u_t *c    The second vector.
 *    @param f32 step      The normalized step.
 *
 *    @return u32         The return code.
 */
u32 vec2u_interp(vec2u_t *a, vec2u_t *b, vec2u_t *c, f32 step) {
    a->x = b->x * (1 - step) + c->x * step;
    a->y = b->y * (1 - step) + c->y * step;

    return 1;
}

/*
 *    Scales a vec2u.
 *
 *    @param vec2u_t *a    The return vector.
 *    @param vec2u_t *b    The vector to scale.
 *    @param f32 scale     The scale.
 *
 *    @return u32         The return code.
 */
u32 vec2u_scale(vec2u_t *a, vec2u_t *b, f32 scale) {
    a->x = b->x * scale;
    a->y = b->y * scale;

    return 1;
}

/*
 *    Subtracts two vec3s.
 *
 *    @param vec3_t *a    The return vector.
 *    @param vec3_t *b    The first vector.
 *    @param vec3_t *c    The second vector.
 *
 *    @return u32        The return code.
 */
u32 vec3_sub(vec3_t *a, vec3_t *b, vec3_t *c) {
    a->x = b->x - c->x;
    a->y = b->y - c->y;
    a->z = b->z - c->z;

    return 1;
}

/*
 *    Interpolates a vec3.
 *
 *    @param vec3_t *a    The return vector.
 *    @param vec3_t *b    The first vector.
 *    @param vec3_t *c    The differential.
 *    @param f32 step     The step.
 *
 *    @return u32        The return code.
 */
u32 vec3_interp(vec3_t *a, vec3_t *b, vec3_t *c, f32 step) {
    a->x = b->x * (1 - step) + c->x * step;
    a->y = b->y * (1 - step) + c->y * step;
    a->z = b->z * (1 - step) + c->z * step;

    return 1;
}

/*
 *    Returns the dot product of two vec3s.
 *
 *    @param vec3_t *a    The first vector.
 *    @param vec3_t *b    The second vector.
 *
 *    @return f32        The dot product.
 */
f32 vec3_dot(vec3_t *a, vec3_t *b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

/*
 *    Returns the legnth of a vec3.
 *
 *    @param vec3_t *a    The vector.
 *
 *    @return f32        The length.
 */
f32 vec3_length(vec3_t *a) {
    return sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);
}

/*
 *    Normalizes a vec3.
 *
 *    @param vec3_t *a    The return vector.
 *    @param vec3_t *b    The vector to normalize.
 *
 *    @return u32        The return code.
 */
u32 vec3_normalize(vec3_t *a, vec3_t *b) {
    f32 len = vec3_length(b);

    if (len == 0.0f) {
        return 0;
    }

    a->x = b->x / len;
    a->y = b->y / len;
    a->z = b->z / len;

    return 1;
}

/*
 *    Crosses two vec3s.
 *
 *    @param vec3_t *a    The return vector.
 *    @param vec3_t *b    The first vector.
 *    @param vec3_t *c    The second vector.
 *
 *    @return u32        The return code.
 */
u32 vec3_cross(vec3_t *a, vec3_t *b, vec3_t *c) {
    a->x = b->y * c->z - b->z * c->y;
    a->y = b->z * c->x - b->x * c->z;
    a->z = b->x * c->y - b->y * c->x;

    return 1;
}

/*
 *    Interpolates a vec4.
 *
 *    @param vec4_t *a    The return vector.
 *    @param vec4_t *b    The first vector.
 *    @param vec4_t *c    The differential.
 *    @param f32 step     The step.
 *
 *    @return u32        The return code.
 */
u32 vec4_interp(vec4_t *a, vec4_t *b, vec4_t *c, f32 step) {
    a->x = b->x * (1 - step) + c->x * step;
    a->y = b->y * (1 - step) + c->y * step;
    a->z = b->z * (1 - step) + c->z * step;
    a->w = b->w * (1 - step) + c->w * step;

    return 1;
}

/*
 *    Interpolates a color32.
 *
 *    @param color32_t *    The return color.
 *    @param color32_t *    The first color.
 *    @param color32_t *    The differential.
 *    @param f32 step       The step.
 *
 *    @return u32           The return code.
 */
u32 color32_interp(color32_t *a, color32_t *b, color32_t *c, f32 step) {
    a->r = b->r + c->r * step;
    a->g = b->g + c->g * step;
    a->b = b->b + c->b * step;
    a->a = b->a + c->a * step;

    return 1;
}

/*
 *    Interpolates a vec.
 *
 *    @param vec_t *ret        The return vector.
 *    @param void *a           The first vector.
 *    @param void *b           The differential.
 *    @param f32 step          The step.
 *    @param v_format_e fmt    The vector format.
 *
 *    @return u32          The return code.
 */
u32 vec_interp(vec_t *ret, void *a, void *b, f32 step, v_format_e fmt) {
    /*
     *    Some vectors are to be implemented.
     */
    switch (fmt) {
    case V_R8G8B8A8_U:
    case V_R8G8B8A8_S:
        return color32_interp(&ret->c32, (color32_t *)a, (color32_t *)b,
                              step);

    case V_R32_U:
        break;
    case V_R32G32_U:
        return vec2u_interp(&ret->v2u, (vec2u_t *)a, (vec2u_t *)b, step);
    case V_R32G32B32_U:
        break;
    case V_R32G32B32A32_U:
        break;

    case V_R32_F:
        break;
    case V_R32G32_F:
        return vec2_interp(&ret->v2, (vec2_t *)a, (vec2_t *)b, step);
    case V_R32G32B32_F:
        return vec3_interp(&ret->v3, (vec3_t *)a, (vec3_t *)b, step);
    case V_R32G32B32A32_F:
        return vec4_interp(&ret->v4, (vec4_t *)a, (vec4_t *)b, step);
    }
}

/*
 *    Scales a vec.
 *
 *    @param vec_t *ret          The return vector.
 *    @param void *a             The vector.
 *    @param f32 scale           The scalar.
 *    @param v_format_e fmt      The vector format.
 *
 *    @return u32          The return code.
 */
u32 vec_scale(vec_t *ret, void *a, f32 scale, v_format_e fmt) {
    /*
     *    Some vectors are to be implemented.
     */
    switch (fmt) {
    case V_R32G32_F:
        return vec2_scale(&ret->v2, (vec2_t *)a, scale);
    case V_R32G32_U:
        return vec2u_scale(&ret->v2u, (vec2u_t *)a, scale);
    }
}

/*
 *    Returns a vec's dot product.
 *
 *    @param void *a           The first vector.
 *    @param void *b           The second vector.
 *    @param v_format_e fmt    The vector format.
 *
 *    @return f32          The dot product.
 */
f32 vec_dot(void *a, void *b, v_format_e fmt) {
    /*
     *    Some vectors are to be implemented.
     */
    switch (fmt) {
    case V_R32G32B32_F:
        return vec3_dot((vec3_t *)a, (vec3_t *)b);
    }
}

/*
 *    Returns the size of a vertex component in bytes.
 *
 *    @param v_format_e fmt     The vertex format.
 *
 *    @return u32           The size of the vertex component in bytes.
 */
u32 get_vertex_component_size(v_format_e fmt) {
    switch (fmt) {
    case V_R8G8B8A8_S:
    case V_R8G8B8A8_U:
        return 4;

    case V_R32_F:
        return 4;
    case V_R32G32_F:
        return 8;
    case V_R32G32B32_F:
        return 12;
    case V_R32G32B32A32_F:
        return 16;
    }
}

/*
 *    Returns a vec's length.
 *
 *    @param void *a          The vector.
 *    @param v_format_e fmt   The vector format.
 *
 *    @return f32          The length.
 */
f32 vec_length(void *a, v_format_e fmt) {
    /*
     *    Some vectors are to be implemented.
     */
    switch (fmt) {
    case V_R32G32B32_F:
        return vec3_length((vec3_t *)a);
    }
}

/*
 *    Normalizes a vec.
 *
 *    @param void *a           The return vector.
 *    @param void *b           The vector to normalize.
 *    @param v_format_e fmt    The vector format.
 *
 *    @return u32          The return code.
 */
u32 vec_normalize(void *a, void *b, v_format_e fmt) {
    /*
     *    Some vectors are to be implemented.
     */
    switch (fmt) {
    case V_R32G32B32_F:
        return vec3_normalize((vec3_t *)a, (vec3_t *)b);
    }
}

/*
 *    Contstructs a plane from three points.
 *
 *    @param plane_t *a    The return plane.
 *    @param vec3_t *b     The first point.
 *    @param vec3_t *c     The second point.
 *    @param vec3_t *d     The third point.
 *
 *    @return u32         The return code.
 */
u32 plane_from_points(plane_t *a, vec3_t *b, vec3_t *c, vec3_t *d) {
    vec3_t v1 = (vec3_t){c->x - b->x, c->y - b->y, c->z - b->z};
    vec3_t v2 = (vec3_t){d->x - b->x, d->y - b->y, d->z - b->z};

    vec3_cross(&a->normal, &v1, &v2);

    a->dist = vec3_dot(&a->normal, b);

    return 1;
}

/*
 *   Returns the distance to a point within a plane.
 *
 *   @param plane_t *a        The plane.
 *   @param vec3_t *b         The point.
 *
 *   @return f32             The distance.
 */
f32 plane_distance(plane_t *a, vec3_t *b) {
    return vec3_dot(&a->normal, b) - a->dist;
}

/*
 *    Swaps the endianness of a 2-byte integer.
 *
 *    @param u16 *a    The integer.
 */
void swap_endian16(u16 *a) { *a = (*a >> 8) | (*a << 8); }

/*
 *    Swaps the endianness of a 4-byte integer.
 *
 *    @param u32 *a    The integer.
 */
void swap_endian32(u32 *a) {
    *a = ((*a >> 24) & 0x000000FF) | ((*a >> 8) & 0x0000FF00) |
         ((*a << 8) & 0x00FF0000) | ((*a << 24) & 0xFF000000);
}