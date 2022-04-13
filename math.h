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

#include "types.h"

#define MAX( a, b ) ( ( a ) > ( b ) ? ( a ) : ( b ) )
#define MIN( a, b ) ( ( a ) < ( b ) ? ( a ) : ( b ) )

/*
 *    Returns a 4x4 identity matrix.
 *
 *    @return mat4_t    The identity matrix.
 */
mat4_t m4_identity( void );

/*
 *    Multiply vec4_t by mat4_t.
 *
 *    @param  vec4_t    The vector to multiply.
 *    @param  mat4_t    The matrix to multiply.
 * 
 *    @return mat4_t    The resulting matrix.
 */
mat4_t v4_mul_m4( vec4_t sVec, mat4_t sMat );

/*
 *   Multiply mat4_t by vec4_t.
 *
 *    @param  mat4_t    The matrix to multiply.
 *    @param  vec4_t    The vector to multiply.
 * 
 *    @return mat4_t    The resulting matrix.
 */
mat4_t m4_mul_v4( mat4_t sMat, vec4_t sVec );

/*
 *    Multiply mat4_t by mat4_t.
 *
 *    @param  mat4_t    The matrix to multiply.
 *    @param  mat4_t    The matrix to multiply.
 * 
 *    @return mat4_t    The resulting matrix.
 */
mat4_t m4_mul_m4( mat4_t sMat1, mat4_t sMat2 );

/*
 *    Generate a rotation matrix.
 *
 *    @param  f32    The angle to rotate by.
 *    @param  vec3_t The axis to rotate around.
 * 
 *    @return mat4_t The resulting matrix.
 */
mat4_t m4_rotate( f32 fAngle, vec3_t sAxis );

/*
 *    Generate a translation matrix.
 *
 *    @param  vec3_t The translation vector.
 *
 *    @return mat4_t The resulting matrix.
 */
mat4_t m4_translate( vec3_t sVec );

/*
 *    Returns a vec2 differential.
 *
 *    @param vec2_t    The first vector.
 *    @param vec2_t    The second vector.
 *    @param f32       The divisor.
 *  
 *    @return vec2_t   The differential.
 */
vec2_t vec2_diff( vec2_t a, vec2_t b, f32 sDivisor );

/*
 *    Interpolates a vec2.
 *
 *    @param vec2_t    The first vector.
 *    @param vec2_t    The differential.
 *    @param f32       The step.
 * 
 *    @return vec2_t   The interpolated vector.
 */
vec2_t vec2_interp( vec2_t a, vec2_t b, f32 sStep );

/*
 *    Interpolates a vec2u.
 *
 *    @param vec2u_t    The first vector.
 *    @param vec2u_t    The second vector.
 *    @param f32        The normalized step.
 * 
 *    @return vec2u_t   The interpolated vector.
 */
vec2u_t vec2u_interp( vec2u_t a, vec2u_t b, f32 sStep );

/*
 *    Returns a vec3 differential.
 *
 *    @param vec3_t    The first vector.
 *    @param vec3_t    The second vector.
 *    @param f32       The divisor.
 *
 *    @return vec3_t   The differential.
 */
vec3_t vec3_diff( vec3_t a, vec3_t b, f32 sDivisor );

/*
 *    Interpolates a vec3.
 *
 *    @param vec3_t    The first vector.
 *    @param vec3_t    The differential.
 *    @param f32       The step.
 *
 *    @return vec3_t   The interpolated vector.
 */
vec3_t vec3_interp( vec3_t a, vec3_t b, f32 sStep );

/*
 *    Returns a vec4 differential.
 *
 *    @param vec4_t    The first vector.
 *    @param vec4_t    The second vector.
 *    @param f32       The divisor.
 *
 *    @return vec4_t   The differential.
 */
vec4_t vec4_diff( vec4_t a, vec4_t b, f32 sDivisor );

/*
 *    Interpolates a vec4.
 *
 *    @param vec4_t    The first vector.
 *    @param vec4_t    The differential.
 *    @param f32       The step.
 * 
 *    @return vec4_t   The interpolated vector.
 */
vec4_t vec4_interp( vec4_t a, vec4_t b, f32 sStep );

/*
 *    Returns a color32 differential.
 *
 *    @param color32_t    The first color.
 *    @param color32_t    The second color.
 *    @param f32          The divisor.
 * 
 *    @return color32_t   The differential.
 */
color32_t color32_diff( color32_t a, color32_t b, f32 sDivisor );

/*
 *    Interpolates a color32.
 *
 *    @param color32_t    The first color.
 *    @param color32_t    The differential.
 *    @param f32          The step.
 * 
 *    @return color32_t   The interpolated color.
 */
color32_t color32_interp( color32_t a, color32_t b, f32 sStep );

/*
 *    Returns a vec differential.
 *
 *    @param void *        The first vector.
 *    @param void *        The second vector.
 *    @param f32           The divisor.
 *    @param v_format_e    The vector format.
 * 
 *    @return vec_t        The differential.
 */
vec_t vec_diff( void *a, void *b, f32 sDivisor, v_format_e sFmt );

/*
 *    Interpolates a vec.
 *
 *    @param void *        The first vector.
 *    @param void *        The differential.
 *    @param f32           The step.
 *    @param v_format_e    The vector format.
 * 
 *    @return vec_t        The interpolated vector.
 */
vec_t vec_interp( void *a, void *b, f32 sStep, v_format_e sFmt );