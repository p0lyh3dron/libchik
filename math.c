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

#if defined( __unix__ ) && ( __i386__ )
    #include <xmmintrin.h>
#elif defined( _WIN32 ) && ( _M_X86 )
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
#if defined( __unix__ ) && defined( __i386__ ) || defined( _WIN32 ) && ( _M_X86 )
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
#else 
    m = ( mat4_t ) {
        sMat1.v[ 0 ] * sMat2.v[ 0 ] + sMat1.v[ 1 ] * sMat2.v[ 4 ] + sMat1.v[ 2 ] * sMat2.v[ 8  ] + sMat1.v[ 3 ] * sMat2.v[ 12 ],
        sMat1.v[ 0 ] * sMat2.v[ 1 ] + sMat1.v[ 1 ] * sMat2.v[ 5 ] + sMat1.v[ 2 ] * sMat2.v[ 9  ] + sMat1.v[ 3 ] * sMat2.v[ 13 ],
        sMat1.v[ 0 ] * sMat2.v[ 2 ] + sMat1.v[ 1 ] * sMat2.v[ 6 ] + sMat1.v[ 2 ] * sMat2.v[ 10 ] + sMat1.v[ 3 ] * sMat2.v[ 14 ],
        sMat1.v[ 0 ] * sMat2.v[ 3 ] + sMat1.v[ 1 ] * sMat2.v[ 7 ] + sMat1.v[ 2 ] * sMat2.v[ 11 ] + sMat1.v[ 3 ] * sMat2.v[ 15 ],

        sMat1.v[ 4 ] * sMat2.v[ 0 ] + sMat1.v[ 5 ] * sMat2.v[ 4 ] + sMat1.v[ 6 ] * sMat2.v[ 8  ] + sMat1.v[ 7 ] * sMat2.v[ 12 ],
        sMat1.v[ 4 ] * sMat2.v[ 1 ] + sMat1.v[ 5 ] * sMat2.v[ 5 ] + sMat1.v[ 6 ] * sMat2.v[ 9  ] + sMat1.v[ 7 ] * sMat2.v[ 13 ],
        sMat1.v[ 4 ] * sMat2.v[ 2 ] + sMat1.v[ 5 ] * sMat2.v[ 6 ] + sMat1.v[ 6 ] * sMat2.v[ 10 ] + sMat1.v[ 7 ] * sMat2.v[ 14 ],
        sMat1.v[ 4 ] * sMat2.v[ 3 ] + sMat1.v[ 5 ] * sMat2.v[ 7 ] + sMat1.v[ 6 ] * sMat2.v[ 11 ] + sMat1.v[ 7 ] * sMat2.v[ 15 ],

        sMat1.v[ 8 ] * sMat2.v[ 0 ] + sMat1.v[ 9 ] * sMat2.v[ 4 ] + sMat1.v[ 10 ] * sMat2.v[ 8  ] + sMat1.v[ 11 ] * sMat2.v[ 12 ],
        sMat1.v[ 8 ] * sMat2.v[ 1 ] + sMat1.v[ 9 ] * sMat2.v[ 5 ] + sMat1.v[ 10 ] * sMat2.v[ 9  ] + sMat1.v[ 11 ] * sMat2.v[ 13 ],
        sMat1.v[ 8 ] * sMat2.v[ 2 ] + sMat1.v[ 9 ] * sMat2.v[ 6 ] + sMat1.v[ 10 ] * sMat2.v[ 10 ] + sMat1.v[ 11 ] * sMat2.v[ 14 ],
        sMat1.v[ 8 ] * sMat2.v[ 3 ] + sMat1.v[ 9 ] * sMat2.v[ 7 ] + sMat1.v[ 10 ] * sMat2.v[ 11 ] + sMat1.v[ 11 ] * sMat2.v[ 15 ],

        sMat1.v[ 12 ] * sMat2.v[ 0 ] + sMat1.v[ 13 ] * sMat2.v[ 4 ] + sMat1.v[ 14 ] * sMat2.v[ 8  ] + sMat1.v[ 15 ] * sMat2.v[ 12 ],
        sMat1.v[ 12 ] * sMat2.v[ 1 ] + sMat1.v[ 13 ] * sMat2.v[ 5 ] + sMat1.v[ 14 ] * sMat2.v[ 9  ] + sMat1.v[ 15 ] * sMat2.v[ 13 ],
        sMat1.v[ 12 ] * sMat2.v[ 2 ] + sMat1.v[ 13 ] * sMat2.v[ 6 ] + sMat1.v[ 14 ] * sMat2.v[ 10 ] + sMat1.v[ 15 ] * sMat2.v[ 14 ],
        sMat1.v[ 12 ] * sMat2.v[ 3 ] + sMat1.v[ 13 ] * sMat2.v[ 7 ] + sMat1.v[ 14 ] * sMat2.v[ 11 ] + sMat1.v[ 15 ] * sMat2.v[ 15 ],
    };
#endif /* __unix__ && __i386__ || _WIN32 && _M_X86  */
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

/*
 *    Returns a vec2 differential.
 *
 *    @param vec2_t    The first vector.
 *    @param vec2_t    The second vector.
 *    @param f32       The divisor.
 *  
 *    @return vec2_t   The differential.
 */
vec2_t vec2_diff( vec2_t a, vec2_t b, f32 sDivisor ) {
    vec2_t v;
    v.x = ( b.x - a.x ) / sDivisor;
    v.y = ( b.y - a.y ) / sDivisor;
    return v;
}

/*
 *    Interpolates a vec2.
 *
 *    @param vec2_t    The first vector.
 *    @param vec2_t    The differential.
 *    @param f32       The step.
 * 
 *    @return vec2_t   The interpolated vector.
 */
vec2_t vec2_interp( vec2_t a, vec2_t b, f32 sStep ) {
    vec2_t v;
    v.x = a.x + b.x * sStep;
    v.y = a.y + b.y * sStep;
    return v;
}

/*
 *    Interpolates a vec2u.
 *
 *    @param vec2u_t    The first vector.
 *    @param vec2u_t    The second vector.
 *    @param f32        The normalized step.
 * 
 *    @return vec2u_t   The interpolated vector.
 */
vec2u_t vec2u_interp( vec2u_t a, vec2u_t b, f32 sStep ) {
    vec2u_t v;
    v.x = a.x * ( 1 - sStep ) + b.x * sStep;
    v.y = a.y * ( 1 - sStep ) + b.y * sStep;
    return v;
}

/*
 *    Returns a vec3 differential.
 *
 *    @param vec3_t    The first vector.
 *    @param vec3_t    The second vector.
 *    @param f32       The divisor.
 *
 *    @return vec3_t   The differential.
 */
vec3_t vec3_diff( vec3_t a, vec3_t b, f32 sDivisor ) {
    vec3_t v;
    v.x = ( b.x - a.x ) / sDivisor;
    v.y = ( b.y - a.y ) / sDivisor;
    v.z = ( b.z - a.z ) / sDivisor;
    return v;
}

/*
 *    Interpolates a vec3.
 *
 *    @param vec3_t    The first vector.
 *    @param vec3_t    The differential.
 *    @param f32       The step.
 *
 *    @return vec3_t   The interpolated vector.
 */
vec3_t vec3_interp( vec3_t a, vec3_t b, f32 sStep ) {
    vec3_t v;
    v.x = a.x + b.x * sStep;
    v.y = a.y + b.y * sStep;
    v.z = a.z + b.z * sStep;
    return v;
}

/*
 *    Returns a vec4 differential.
 *
 *    @param vec4_t    The first vector.
 *    @param vec4_t    The second vector.
 *    @param f32       The divisor.
 *
 *    @return vec4_t   The differential.
 */
vec4_t vec4_diff( vec4_t a, vec4_t b, f32 sDivisor ) {
    vec4_t v;
    v.x = ( b.x - a.x ) / sDivisor;
    v.y = ( b.y - a.y ) / sDivisor;
    v.z = ( b.z - a.z ) / sDivisor;
    v.w = ( b.w - a.w ) / sDivisor;
    return v;
}

/*
 *    Interpolates a vec4.
 *
 *    @param vec4_t    The first vector.
 *    @param vec4_t    The second vector.
 *    @param f32       The normalised step.
 * 
 *    @return vec4_t   The interpolated vector.
 */
vec4_t vec4_interp( vec4_t a, vec4_t b, f32 sStep ) {
    vec4_t v;
    v.x = a.x * ( 1 - sStep ) + b.x * sStep;
    v.y = a.y * ( 1 - sStep ) + b.y * sStep;
    v.z = a.z * ( 1 - sStep ) + b.z * sStep;
    v.w = a.w * ( 1 - sStep ) + b.w * sStep;
    return v;
}

/*
 *    Returns a color32 differential.
 *
 *    @param color32_t    The first color.
 *    @param color32_t    The second color.
 *    @param f32          The divisor.
 * 
 *    @return color32_t   The differential.
 */
color32_t color32_diff( color32_t a, color32_t b, f32 sDivisor ) {
    color32_t c;
    c.r = ( b.r - a.r ) / sDivisor;
    c.g = ( b.g - a.g ) / sDivisor;
    c.b = ( b.b - a.b ) / sDivisor;
    c.a = ( b.a - a.a ) / sDivisor;
    return c;
}

/*
 *    Interpolates a color32.
 *
 *    @param color32_t    The first color.
 *    @param color32_t    The differential.
 *    @param f32          The step.
 * 
 *    @return color32_t   The interpolated color.
 */
color32_t color32_interp( color32_t a, color32_t b, f32 sStep ) {
    color32_t c;
    c.r = a.r + b.r * sStep;
    c.g = a.g + b.g * sStep;
    c.b = a.b + b.b * sStep;
    c.a = a.a + b.a * sStep;
    return c;
}

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
vec_t vec_diff( void *a, void *b, f32 sDivisor, v_format_e sFmt ) {
    if ( a == 0 || b == 0 ) {
        log_warn( "vec_diff( void *, void *, f32, v_format_e ): a or b is null\n" );
        return ( vec_t ){ 0.0f };
    }
    switch ( sFmt ) {
        case V_R8G8B8A8_U:
        case V_R8G8B8A8_S:
            return ( vec_t ){ .c32 = color32_diff( *( color32_t * )a, *( color32_t * )b, sDivisor ) };

        /*
         *    To be implemented.
         */
        case V_R32_F: break;
        case V_R32G32_F:
            return ( vec_t ){ .v2 = vec2_diff( *( vec2_t * )a, *( vec2_t * )b, sDivisor ) };
        case V_R32G32B32_F:
            return ( vec_t ){ .v3 = vec3_diff( *( vec3_t * )a, *( vec3_t * )b, sDivisor ) };
        case V_R32G32B32A32_F:
            return ( vec_t ){ .v4 = vec4_diff( *( vec4_t * )a, *( vec4_t * )b, sDivisor ) };
    }
}

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
vec_t vec_interp( void *a, void *b, f32 sStep, v_format_e sFmt ) {
    /*
     *    Some vectors are to be implemented.
     */
    switch ( sFmt ) {
        case V_R8G8B8A8_U:
        case V_R8G8B8A8_S:
            return ( vec_t ){ .c32 = color32_interp( *( color32_t * )a, *( color32_t * )b, sStep ) };

        case V_R32_U: break;
        case V_R32G32_U:
            return ( vec_t ){ .v2u = vec2u_interp( *( vec2u_t * )a, *( vec2u_t * )b, sStep ) };
        case V_R32G32B32_U: break;
        case V_R32G32B32A32_U: break;

        
        case V_R32_F: break;
        case V_R32G32_F:
            return ( vec_t ){ .v2 = vec2_interp( *( vec2_t * )a, *( vec2_t * )b, sStep ) };
        case V_R32G32B32_F:
            return ( vec_t ){ .v3 = vec3_interp( *( vec3_t * )a, *( vec3_t * )b, sStep ) };
        case V_R32G32B32A32_F:
            return ( vec_t ){ .v4 = vec4_interp( *( vec4_t * )a, *( vec4_t * )b, sStep ) };
    }
}

/*
 *    Returns the size of a vertex component in bytes.
 *
 *    @param v_format_e     The vertex format.
 * 
 *    @return u32           The size of the vertex component in bytes.
 */
u32 get_vertex_component_size( v_format_e sFmt ) {
    switch ( sFmt ) {
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