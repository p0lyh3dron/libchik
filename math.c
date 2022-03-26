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

#include <math.h>

#if __unix__
    #include <xmmintrin.h>
#elif _WIN32
    #include <intrin.h>
#endif /* __unix__  */

/*
 *    Returns a 4x4 identity matrix.
 *
 *    @return mat4_t    The identity matrix.
 */
mat4_t m4_identity( void ) {
    mat4_t sMat = {
        { 1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1 }
    };
    return sMat;
}

/*
 *    Multiply vec4_t by mat4_t.
 *
 *    @param  vec4_t    The vector to multiply.
 *    @param  mat4_t    The matrix to multiply.
 * 
 *    @return mat4_t    The resulting matrix.
 */
mat4_t v4_mul_m4( vec4_t sVec, mat4_t sMat ) {
    mat4_t m;

    /*
     *    Extend the vector to a 4x1 matrix.
     */

    return m;
}

/*
 *   Multiply mat4_t by vec4_t.
 *
 *    @param  mat4_t    The matrix to multiply.
 *    @param  vec4_t    The vector to multiply.
 * 
 *    @return mat4_t    The resulting matrix.
 */
mat4_t m4_mul_v4( mat4_t sMat, vec4_t sVec ) {

    mat4_t m =  {
        sVec.x, 0, 0, 0,
        sVec.y, 0, 0, 0,
        sVec.z, 0, 0, 0,
        sVec.w, 0, 0, 0
    };

    return m4_mul_m4( sMat, m );
}

/*
 *    Multiply mat4_t by mat4_t.
 *
 *    @param  mat4_t    The matrix to multiply.
 *    @param  mat4_t    The matrix to multiply.
 * 
 *    @return mat4_t    The resulting matrix.
 */
mat4_t m4_mul_m4( mat4_t sMat1, mat4_t sMat2 ) {
    mat4_t m;

    __m128 r0 = _mm_load_ps( &sMat2.v[ 0 ] );
    __m128 r1 = _mm_load_ps( &sMat2.v[ 4 ] );
    __m128 r2 = _mm_load_ps( &sMat2.v[ 8 ] );
    __m128 r3 = _mm_load_ps( &sMat2.v[ 12 ] );

    for ( u32 i = 0; i < 4; ++i ) {
        __m128 r0_ = _mm_set1_ps( sMat1.v[ i * 4 + 0 ] );
        __m128 r1_ = _mm_set1_ps( sMat1.v[ i * 4 + 1 ] );
        __m128 r2_ = _mm_set1_ps( sMat1.v[ i * 4 + 2 ] );
        __m128 r3_ = _mm_set1_ps( sMat1.v[ i * 4 + 3 ] );

        __m128 r   = _mm_add_ps( 
            _mm_add_ps( 
                _mm_mul_ps( r0_, r0 ), 
                _mm_mul_ps( r1_, r1 ) 
            ), 
            _mm_add_ps( 
                _mm_mul_ps( r2_, r2 ), 
                _mm_mul_ps( r3_, r3 ) 
            ) 
        );

        _mm_store_ps( &m.v[ i * 4 + 0 ], r );
    }

    return m;
}

/*
 *    Generate a rotation matrix.
 *
 *    @param  f32    The angle to rotate by.
 *    @param  vec3_t The axis to rotate around.
 * 
 *    @return mat4_t The resulting matrix.
 */
mat4_t m4_rotate( f32 fAngle, vec3_t sAxis ) {
    if ( sAxis.x == 0.0f && sAxis.y == 0.0f && sAxis.z == 0.0f ) {
        return m4_identity();
    }
    /*
     *    TODO: Implement rotation about an arbitrary axis.
     */
    if ( sAxis.x != 0.0f ) {
        mat4_t m = {
            { 1, 0, 0, 0,
              0, cosf( fAngle ), -sinf( fAngle ), 0,
              0, sinf( fAngle ),  cosf( fAngle ), 0,
              0, 0, 0, 1 }
        };
        return m;
    }
    if ( sAxis.y != 0.0f ) {
        mat4_t m = {
            { cosf( fAngle ),  0, sinf( fAngle ), 0,
              0, 1, 0, 0,
              -sinf( fAngle ), 0, cosf( fAngle ), 0,
              0, 0, 0, 1 }
        };
        return m;
    }
    if ( sAxis.z != 0.0f ) {
        mat4_t m = {
            { cosf( fAngle ), -sinf( fAngle ), 0, 0,
              sinf( fAngle ),  cosf( fAngle ), 0, 0,
              0, 0, 1, 0,
              0, 0, 0, 1 }
        };
        return m;
    }
    return m4_identity();
}

/*
 *    Generate a translation matrix.
 *
 *    @param  vec3_t The translation vector.
 *
 *    @return mat4_t The resulting matrix.
 */
mat4_t m4_translate( vec3_t sVec ) {
    mat4_t m = {
        { 1, 0, 0, sVec.x,
          0, 1, 0, sVec.y,
          0, 0, 1, sVec.z,
          0, 0, 0, 1 }
    };
    return m;
}