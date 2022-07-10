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
//#if defined( __unix__ ) && defined( __i386__ ) || defined( _WIN32 ) && ( _M_X86 )
#if 1
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
 *    Interpolates a vec2.
 *
 *    @param vec2_t *    The return vector.
 *    @param vec2_t *    The first vector.
 *    @param vec2_t *    The differential.
 *    @param f32         The step.
 * 
 *    @return u32        The return code.
 */
u32 vec2_interp( vec2_t *a, vec2_t *b, vec2_t *c, f32 sStep ) {
    a->x = b->x * ( 1 - sStep ) + c->x * sStep;
    a->y = b->y * ( 1 - sStep ) + c->y * sStep;

    return 1;
}

/*
 *    Scales a vec2.
 *
 *    @param vec2_t *    The return vector.
 *    @param vec2_t *    The vector to scale.
 *    @param f32         The scale.
 * 
 *    @return u32        The return code.
 */
u32 vec2_scale( vec2_t *a, vec2_t *b, f32 sScale ) {
    a->x = b->x * sScale;
    a->y = b->y * sScale;

    return 1;
}

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
u32 vec2u_interp( vec2u_t *a, vec2u_t *b, vec2u_t *c, f32 sStep ) {
    a->x = b->x * ( 1 - sStep ) + c->x * sStep;
    a->y = b->y * ( 1 - sStep ) + c->y * sStep;

    return 1;
}

/*
 *    Scales a vec2u.
 *    
 *    @param vec2u_t *    The return vector.
 *    @param vec2u_t *    The vector to scale.
 *    @param f32          The scale.
 * 
 *    @return u32         The return code.
 */
u32 vec2u_scale( vec2u_t *a, vec2u_t *b, f32 sScale ) {
    a->x = b->x * sScale;
    a->y = b->y * sScale;

    return 1;
}

/*
 *    Subtracts two vec3s.
 *
 *    @param vec3_t *    The return vector.
 *    @param vec3_t *    The first vector.
 *    @param vec3_t *    The second vector.
 * 
 *    @return u32        The return code.
 */
u32 vec3_sub( vec3_t *a, vec3_t *b, vec3_t *c ) {
    a->x = b->x - c->x;
    a->y = b->y - c->y;
    a->z = b->z - c->z;

    return 1;
}

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
u32 vec3_interp( vec3_t *a, vec3_t *b, vec3_t *c, f32 sStep ) {
    a->x = b->x * ( 1 - sStep ) + c->x * sStep;
    a->y = b->y * ( 1 - sStep ) + c->y * sStep;
    a->z = b->z * ( 1 - sStep ) + c->z * sStep;
  
    return 1;
}

/*
 *    Returns the dot product of two vec3s.
 *
 *    @param vec3_t *    The first vector.
 *    @param vec3_t *    The second vector.
 * 
 *    @return f32        The dot product.
 */
f32 vec3_dot( vec3_t *a, vec3_t *b ) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

/*
 *    Returns the legnth of a vec3.
 *
 *    @param vec3_t *    The vector.
 *
 *    @return f32        The length.
 */
f32 vec3_length( vec3_t *a ) {
    return sqrtf( a->x * a->x + a->y * a->y + a->z * a->z );
}

/*
 *    Normalizes a vec3.
 *
 *    @param vec3_t *    The return vector.
 *    @param vec3_t *    The vector to normalize.
 * 
 *    @return u32        The return code.
 */
u32 vec3_normalize( vec3_t *a, vec3_t *b ) {
    f32 len = vec3_length( b );

    if ( len == 0.0f ) {
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
 *    @param vec3_t *    The return vector.
 *    @param vec3_t *    The first vector.
 *    @param vec3_t *    The second vector.
 * 
 *    @return u32        The return code.
 */
u32 vec3_cross( vec3_t *a, vec3_t *b, vec3_t *c ) {
    a->x = b->y * c->z - b->z * c->y;
    a->y = b->z * c->x - b->x * c->z;
    a->z = b->x * c->y - b->y * c->x;

    return 1;
}

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
u32 vec4_interp( vec4_t *a, vec4_t *b, vec4_t *c, f32 sStep ) {
    a->x = b->x * ( 1 - sStep ) + c->x * sStep;
    a->y = b->y * ( 1 - sStep ) + c->y * sStep;
    a->z = b->z * ( 1 - sStep ) + c->z * sStep;
    a->w = b->w * ( 1 - sStep ) + c->w * sStep;

    return 1;
}

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
u32 color32_interp( color32_t *a, color32_t *b, color32_t *c, f32 sStep ) {
    a->r = b->r + c->r * sStep;
    a->g = b->g + c->g * sStep;
    a->b = b->b + c->b * sStep;
    a->a = b->a + c->a * sStep;

    return 1;
}

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
u32 vec_interp( vec_t *spRet, void *a, void *b, f32 sStep, v_format_e sFmt ) {
    /*
     *    Some vectors are to be implemented.
     */
    switch ( sFmt ) {
        case V_R8G8B8A8_U:
        case V_R8G8B8A8_S:
            return color32_interp( &spRet->c32, ( color32_t * ) a, ( color32_t * ) b, sStep );

        case V_R32_U: break;
        case V_R32G32_U:
            return vec2u_interp( &spRet->v2u, ( vec2u_t * )a, ( vec2u_t * )b, sStep );
        case V_R32G32B32_U: break;
        case V_R32G32B32A32_U: break;

        
        case V_R32_F: break;
        case V_R32G32_F:
            return vec2_interp( &spRet->v2, ( vec2_t * )a, ( vec2_t * )b, sStep );
        case V_R32G32B32_F:
            return vec3_interp( &spRet->v3, ( vec3_t * )a, ( vec3_t * )b, sStep );
        case V_R32G32B32A32_F:
            return vec4_interp( &spRet->v4, ( vec4_t * )a, ( vec4_t * )b, sStep );
    }
}


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
u32 vec_scale( vec_t *spRet, void *a, f32 sScale, v_format_e sFmt ) {
    /*
     *    Some vectors are to be implemented.
     */
    switch ( sFmt ) {
        case V_R32G32_F:
            return vec2_scale( &spRet->v2, ( vec2_t * )a, sScale );
        case V_R32G32_U:
            return vec2u_scale( &spRet->v2u, ( vec2u_t * )a, sScale );
    }
}

/*
 *    Returns a vec's dot product.
 *
 *    @param void *        The first vector.
 *    @param void *        The second vector.
 *    @param v_format_e    The vector format.
 * 
 *    @return f32          The dot product.
 */
f32 vec_dot( void *a, void *b, v_format_e sFmt ) {
    /*
     *    Some vectors are to be implemented.
     */
    switch ( sFmt ) {
        case V_R32G32B32_F:
            return vec3_dot( ( vec3_t * )a, ( vec3_t * )b );
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

/*
 *    Returns a vec's length.
 *
 *    @param void *        The vector.
 *    @param v_format_e    The vector format.
 * 
 *    @return f32          The length.
 */
f32 vec_length( void *a, v_format_e sFmt ) {
    /*
     *    Some vectors are to be implemented.
     */
    switch ( sFmt ) {
        case V_R32G32B32_F:
            return vec3_length( ( vec3_t * )a );
    }
}

/*
 *    Normalizes a vec.
 *
 *    @param void *        The return vector.
 *    @param void *        The vector to normalize.
 *    @param v_format_e    The vector format.
 *
 *    @return u32          The return code.
 */
u32 vec_normalize( void *a, void *b, v_format_e sFmt ) {
    /*
     *    Some vectors are to be implemented.
     */
    switch ( sFmt ) {
        case V_R32G32B32_F:
            return vec3_normalize( ( vec3_t * )a, ( vec3_t * )b );
    }
}

/*
 *    Contstructs a plane from three points.
 *
 *    @param plane_t *    The return plane.
 *    @param vec3_t *     The first point.
 *    @param vec3_t *     The second point.
 *    @param vec3_t *     The third point.
 * 
 *    @return u32         The return code.
 */
u32 plane_from_points( plane_t *a, vec3_t *b, vec3_t *c, vec3_t *d ) {
    vec3_t v1 = ( vec3_t ){ c->x - b->x, c->y - b->y, c->z - b->z };
    vec3_t v2 = ( vec3_t ){ d->x - b->x, d->y - b->y, d->z - b->z };

    vec3_cross( &a->aNormal, &v1, &v2 );

    a->aDistance = vec3_dot( &a->aNormal, b );

    return 1;
}

/*
 *   Returns the distance to a point within a plane.
 *
 *   @param plane_t *        The plane.
 *   @param vec3_t *         The point.
 *
 *   @return f32             The distance.
 */
f32 plane_distance( plane_t *a, vec3_t *b ) {
    return vec3_dot( &a->aNormal, b ) - a->aDistance;
}

/*
 *    Swaps the endianness of a 2-byte integer.
 *
 *    @param u16 *    The integer.
 */
void swap_endian16( u16 *a ) {
    *a = ( *a >> 8 ) | ( *a << 8 );
}

/*
 *    Swaps the endianness of a 4-byte integer.
 *
 *    @param u32 *    The integer.
 */
void swap_endian32( u32 *a ) {
    *a = ( ( *a >> 24 ) & 0x000000FF ) | ( ( *a >> 8 ) & 0x0000FF00 ) | ( ( *a << 8 ) & 0x00FF0000 ) | ( ( *a << 24 ) & 0xFF000000 );
}