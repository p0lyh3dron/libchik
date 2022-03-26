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