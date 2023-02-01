/*
 *    math.h    --    math operations
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 25, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    Included here are the functions for the math library.
 */
#pragma once

#include <math.h>

#include "types.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define PI                                                                     \
    3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

#define ANGLE_TO_RADIAN(a) ((a)*PI / 180.0f)
#define RADIAN_TO_ANGLE(a) ((a)*180.0f / PI)

/*
 *    Returns a 4x4 identity matrix.
 *
 *    @return mat4_t    The identity matrix.
 */
mat4_t m4_identity(void);

/*
 *    Multiply vec4_t by mat4_t.
 *
 *    @param  vec4_t vec    The vector to multiply.
 *    @param  mat4_t mat    The matrix to multiply.
 *
 *    @return mat4_t    The resulting matrix.
 */
mat4_t v4_mul_m4(vec4_t vec, mat4_t mat);

/*
 *   Multiply mat4_t by vec4_t.
 *
 *    @param  mat4_t mat    The matrix to multiply.
 *    @param  vec4_t vec    The vector to multiply.
 *
 *    @return mat4_t    The resulting matrix.
 */
mat4_t m4_mul_v4(mat4_t mat, vec4_t vec);

/*
 *    Multiply mat4_t by mat4_t.
 *
 *    @param  mat4_t mat1    The matrix to multiply.
 *    @param  mat4_t mat2    The matrix to multiply.
 *
 *    @return mat4_t    The resulting matrix.
 */
mat4_t m4_mul_m4(mat4_t mat1, mat4_t mat2);

/*
 *    Generate a rotation matrix.
 *
 *    @param  f32 ang     The angle to rotate by.
 *    @param  vec3_t axis The axis to rotate around.
 *
 *    @return mat4_t The resulting matrix.
 */
mat4_t m4_rotate(f32 ang, vec3_t axis);

/*
 *    Generate a translation matrix.
 *
 *    @param  vec3_t vec The translation vector.
 *
 *    @return mat4_t The resulting matrix.
 */
mat4_t m4_translate(vec3_t vec);

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
u32 vec2_interp(vec2_t *a, vec2_t *b, vec2_t *c, f32 step);

/*
 *    Scales a vec2.
 *
 *    @param vec2_t *a    The return vector.
 *    @param vec2_t *b    The vector to scale.
 *    @param f32 scale    The scale.
 *
 *    @return u32        The return code.
 */
u32 vec2_scale(vec2_t *a, vec2_t *b, f32 scale);

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
u32 vec2u_interp(vec2u_t *a, vec2u_t *b, vec2u_t *c, f32 step);

/*
 *    Scales a vec2u.
 *
 *    @param vec2u_t *a    The return vector.
 *    @param vec2u_t *b    The vector to scale.
 *    @param f32 scale     The scale.
 *
 *    @return u32         The return code.
 */
u32 vec2u_scale(vec2u_t *a, vec2u_t *b, f32 scale);

/*
 *    Subtracts two vec3s.
 *
 *    @param vec3_t *a    The return vector.
 *    @param vec3_t *b    The first vector.
 *    @param vec3_t *c    The second vector.
 *
 *    @return u32        The return code.
 */
u32 vec3_sub(vec3_t *a, vec3_t *b, vec3_t *c);

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
u32 vec3_interp(vec3_t *a, vec3_t *b, vec3_t *c, f32 step);

/*
 *    Returns the dot product of two vec3s.
 *
 *    @param vec3_t *a    The first vector.
 *    @param vec3_t *b    The second vector.
 *
 *    @return f32        The dot product.
 */
f32 vec3_dot(vec3_t *a, vec3_t *b);

/*
 *    Returns the legnth of a vec3.
 *
 *    @param vec3_t *a    The vector.
 *
 *    @return f32        The length.
 */
f32 vec3_length(vec3_t *a);

/*
 *    Normalizes a vec3.
 *
 *    @param vec3_t *a    The return vector.
 *    @param vec3_t *b    The vector to normalize.
 *
 *    @return u32        The return code.
 */
u32 vec3_normalize(vec3_t *a, vec3_t *b);

/*
 *    Crosses two vec3s.
 *
 *    @param vec3_t *a    The return vector.
 *    @param vec3_t *b    The first vector.
 *    @param vec3_t *c    The second vector.
 *
 *    @return u32        The return code.
 */
u32 vec3_cross(vec3_t *a, vec3_t *b, vec3_t *c);

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
u32 vec4_interp(vec4_t *a, vec4_t *b, vec4_t *c, f32 step);

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
u32 color32_interp(color32_t *a, color32_t *b, color32_t *c, f32 step);

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
u32 vec_interp(vec_t *ret, void *a, void *b, f32 step, v_format_e fmt);

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
u32 vec_scale(vec_t *ret, void *a, f32 scale, v_format_e fmt);

/*
 *    Returns a vec's dot product.
 *
 *    @param void *a           The first vector.
 *    @param void *b           The second vector.
 *    @param v_format_e fmt    The vector format.
 *
 *    @return f32          The dot product.
 */
f32 vec_dot(void *a, void *b, v_format_e fmt);

/*
 *    Returns the size of a vertex component in bytes.
 *
 *    @param v_format_e fmt     The vertex format.
 *
 *    @return u32           The size of the vertex component in bytes.
 */
u32 get_vertex_component_size(v_format_e fmt);

/*
 *    Returns a vec's length.
 *
 *    @param void *a          The vector.
 *    @param v_format_e fmt   The vector format.
 *
 *    @return f32          The length.
 */
f32 vec_length(void *a, v_format_e fmt);

/*
 *    Normalizes a vec.
 *
 *    @param void *a           The return vector.
 *    @param void *b           The vector to normalize.
 *    @param v_format_e fmt    The vector format.
 *
 *    @return u32          The return code.
 */
u32 vec_normalize(void *a, void *b, v_format_e fmt);

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
u32 plane_from_points(plane_t *a, vec3_t *b, vec3_t *c, vec3_t *d);

/*
 *   Returns the distance to a point within a plane.
 *
 *   @param plane_t *a        The plane.
 *   @param vec3_t *b         The point.
 *
 *   @return f32             The distance.
 */
f32 plane_distance(plane_t *a, vec3_t *b);

/*
 *    Swaps the endianness of a 2-byte integer.
 *
 *    @param u16 *a    The integer.
 */
void swap_endian16(u16 *a);

/*
 *    Swaps the endianness of a 4-byte integer.
 *
 *    @param u32 *a    The integer.
 */
void swap_endian32(u32 *a);