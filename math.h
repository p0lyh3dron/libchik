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
 *    Interpolates a vec2.
 *
 *    @param vec2_t *    The return vector.
 *    @param vec2_t *    The first vector.
 *    @param vec2_t *    The differential.
 *    @param f32         The step.
 * 
 *    @return u32        The return code.
 */
u32 vec2_interp( vec2_t *a, vec2_t *b, vec2_t *c, f32 sStep );

/*
 *    Scales a vec2.
 *
 *    @param vec2_t *    The return vector.
 *    @param vec2_t *    The vector to scale.
 *    @param f32         The scale.
 * 
 *    @return u32        The return code.
 */
u32 vec2_scale( vec2_t *a, vec2_t *b, f32 sScale );

/*
 *    Interpolates a vec2u.
 *
 *    @param vec2u_t *    The return vector.
 *    @param vec2u_t *    The first vector.
 *    @param vec2u_t *    The second vector.
 *    @param f32          The normalized step.
 * 
 *    @return u32         The return code.
 */
u32 vec2u_interp( vec2u_t *a, vec2u_t *b, vec2u_t *c, f32 sStep );

/*
 *    Scales a vec2u.
 *    
 *    @param vec2u_t *    The return vector.
 *    @param vec2u_t *    The vector to scale.
 *    @param f32          The scale.
 * 
 *    @return u32         The return code.
 */
u32 vec2u_scale( vec2u_t *a, vec2u_t *b, f32 sScale );

/*
 *    Interpolates a vec3.
 *
 *    @param vec3_t *    The return vector.
 *    @param vec3_t *    The first vector.
 *    @param vec3_t *    The differential.
 *    @param f32         The step.
 *
 *    @return u32        The return code.
 */
u32 vec3_interp( vec3_t *a, vec3_t *b, vec3_t *c, f32 sStep );

/*
 *    Interpolates a vec4.
 *
 *    @param vec4_t *    The return vector.
 *    @param vec4_t *    The first vector.
 *    @param vec4_t *    The differential.
 *    @param f32         The step.
 * 
 *    @return u32        The return code.
 */
u32 vec4_interp( vec4_t *a, vec4_t *b, vec4_t *c, f32 sStep );

/*
 *    Interpolates a color32.
 *
 *    @param color32_t *    The return color.
 *    @param color32_t *    The first color.
 *    @param color32_t *    The differential.
 *    @param f32            The step.
 * 
 *    @return u32           The return code.
 */
u32 color32_interp( color32_t *a, color32_t *b, color32_t *c, f32 sStep );

/*
 *    Interpolates a vec.
 *
 *    @param vec_t *       The return vector.
 *    @param void *        The first vector.
 *    @param void *        The differential.
 *    @param f32           The step.
 *    @param v_format_e    The vector format.
 * 
 *    @return u32          The return code.
 */
u32 vec_interp( vec_t *spRet, void *a, void *b, f32 sStep, v_format_e sFmt );

/*
 *    Scales a vec.
 *
 *    @param vec_t *       The return vector.
 *    @param void *        The vector.
 *    @param f32           The scalar.
 *    @param v_format_e    The vector format.
 * 
 *    @return u32          The return code.
 */
u32 vec_scale( vec_t *spRet, void *a, f32 sScale, v_format_e sFmt );