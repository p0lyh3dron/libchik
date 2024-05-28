/*
 *    lchik_math.c    --    math operations
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 25, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file defines the functions used for math operations.
 */
#include "lchik_math.h"

// #if defined( __unix__ ) && ( __i386__ )
#if 1
#include <xmmintrin.h>
#elif defined(_WIN32) && (_M_X86)
#include <intrin.h>
#endif /* __unix__  */

const unsigned int _crc32_table[] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3,	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de,	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,	0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5,	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,	0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940,	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,	0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

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

    mat4_t m = {vec.x, 0, 0, 0, vec.y, 0, 0, 0, vec.z, 0, 0, 0, vec.w, 0, 0, 0};

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
    mat4_t        m;
// #if defined( __unix__ ) && defined( __i386__ ) || defined( _WIN32 ) && (
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
 *    @param  float ang     The angle to rotate by.
 *    @param  vec3_t axis The axis to rotate around.
 *
 *    @return mat4_t The resulting matrix.
 */
mat4_t m4_rotate(float ang, vec3_t axis) {
    if (axis.x == 0.0f && axis.y == 0.0f && axis.z == 0.0f) {
        return m4_identity();
    }
    /*
     *    TODO: Implement rotation about an arbitrary axis.
     */
    if (axis.x != 0.0f) {
        mat4_t m = {{1, 0, 0, 0, 0, cosf(ang), -sinf(ang), 0, 0, sinf(ang),
                     cosf(ang), 0, 0, 0, 0, 1}};
        return m;
    }
    if (axis.y != 0.0f) {
        mat4_t m = {{cosf(ang), 0, sinf(ang), 0, 0, 1, 0, 0, -sinf(ang), 0,
                     cosf(ang), 0, 0, 0, 0, 1}};
        return m;
    }
    if (axis.z != 0.0f) {
        mat4_t m = {{cosf(ang), -sinf(ang), 0, 0, sinf(ang), cosf(ang), 0, 0, 0,
                     0, 1, 0, 0, 0, 0, 1}};
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
    mat4_t m = {{1, 0, 0, vec.x, 0, 1, 0, vec.y, 0, 0, 1, vec.z, 0, 0, 0, 1}};
    return m;
}

/*
 *     Adds a vec2.
 *
 *     @param vec2_t *a    The return vector.
 *     @param vec2_t *b    The first vector.
 *     @param vec2_t *c    The second vector.
 * 
 *     @return unsigned int        The return code.
 */
unsigned int vec2_add(vec2_t *a, vec2_t *b, vec2_t *c) {
    a->x = b->x + c->x;
    a->y = b->y + c->y;

    return 1;
}

/*
 *    Subtracts a vec2.
 *
 *    @param vec2_t *a    The return vector.
 *    @param vec2_t *b    The first vector.
 *    @param vec2_t *c    The second vector.
 *
 *    @return unsigned int        The return code.
 */
unsigned int vec2_sub(vec2_t *a, vec2_t *b, vec2_t *c) {
    a->x = b->x - c->x;
    a->y = b->y - c->y;

    return 1;
}

/*
 *    Interpolates a vec2.
 *
 *    @param vec2_t *a    The return vector.
 *    @param vec2_t *b    The first vector.
 *    @param vec2_t *c    The differential.
 *    @param float step     The step.
 *
 *    @return unsigned int        The return code.
 */
unsigned int vec2_interp(vec2_t *a, vec2_t *b, vec2_t *c, float step) {
    a->x = b->x * (1 - step) + c->x * step;
    a->y = b->y * (1 - step) + c->y * step;

    return 1;
}

/*
 *    Scales a vec2.
 *
 *    @param vec2_t *a    The return vector.
 *    @param vec2_t *b    The vector to scale.
 *    @param float scale    The scale.
 *
 *    @return unsigned int        The return code.
 */
unsigned int vec2_scale(vec2_t *a, vec2_t *b, float scale) {
    a->x = b->x * scale;
    a->y = b->y * scale;

    return 1;
}

/*
 *    Returns the magnitude of a vec2.
 *
 *    @param vec2_t *a    The vector.
 * 
 *    @return float        The magnitude.
 */
float vec2_mag(vec2_t *a) {
    return sqrtf(a->x * a->x + a->y * a->y);
}

/*
 *    Interpolates a vec2u.
 *
 *    @param vec2u_t *a    The return vector.
 *    @param vec2u_t *b    The first vector.
 *    @param vec2u_t *c    The second vector.
 *    @param float step      The normalized step.
 *
 *    @return unsigned int         The return code.
 */
unsigned int vec2u_interp(vec2u_t *a, vec2u_t *b, vec2u_t *c, float step) {
    a->x = b->x * (1 - step) + c->x * step;
    a->y = b->y * (1 - step) + c->y * step;

    return 1;
}

/*
 *    Scales a vec2u.
 *
 *    @param vec2u_t *a    The return vector.
 *    @param vec2u_t *b    The vector to scale.
 *    @param float scale     The scale.
 *
 *    @return unsigned int         The return code.
 */
unsigned int vec2u_scale(vec2u_t *a, vec2u_t *b, float scale) {
    a->x = b->x * scale;
    a->y = b->y * scale;

    return 1;
}

/*
 *    Adds two vec3s.
 *
 *    @param vec3_t *a    The return vector.
 *    @param vec3_t *b    The first vector.
 *    @param vec3_t *c    The second vector.
 * 
 *    @return unsigned int        The return code.
 */
unsigned int vec3_add(vec3_t *a, vec3_t *b, vec3_t *c) {
    a->x = b->x + c->x;
    a->y = b->y + c->y;
    a->z = b->z + c->z;

    return 1;
}

/*
 *    Subtracts two vec3s.
 *
 *    @param vec3_t *a    The return vector.
 *    @param vec3_t *b    The first vector.
 *    @param vec3_t *c    The second vector.
 *
 *    @return unsigned int        The return code.
 */
unsigned int vec3_sub(vec3_t *a, vec3_t *b, vec3_t *c) {
    a->x = b->x - c->x;
    a->y = b->y - c->y;
    a->z = b->z - c->z;

    return 1;
}

/*
 *    Scales a vec3.
 *
 *    @param vec3_t *a       The return vector.
 *    @param vec3_t *b       The vector to scale.
 *    @param float scale     The scale.
 * 
 *    @return unsigned int        The return code.
 */
unsigned int vec3_scale(vec3_t *a, vec3_t *b, float scale) {
    a->x = b->x * scale;
    a->y = b->y * scale;
    a->z = b->z * scale;

    return 1;
}

/*
 *    Interpolates a vec3.
 *
 *    @param vec3_t *a    The return vector.
 *    @param vec3_t *b    The first vector.
 *    @param vec3_t *c    The differential.
 *    @param float step     The step.
 *
 *    @return unsigned int        The return code.
 */
unsigned int vec3_interp(vec3_t *a, vec3_t *b, vec3_t *c, float step) {
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
 *    @return float        The dot product.
 */
float vec3_dot(vec3_t *a, vec3_t *b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

/*
 *    Returns the legnth of a vec3.
 *
 *    @param vec3_t *a    The vector.
 *
 *    @return float        The length.
 */
float vec3_length(vec3_t *a) {
    return sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);
}

/*
 *    Normalizes a vec3.
 *
 *    @param vec3_t *a    The return vector.
 *    @param vec3_t *b    The vector to normalize.
 *
 *    @return unsigned int        The return code.
 */
unsigned int vec3_normalize(vec3_t *a, vec3_t *b) {
    float len = vec3_length(b);

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
 *    @return unsigned int        The return code.
 */
unsigned int vec3_cross(vec3_t *a, vec3_t *b, vec3_t *c) {
    a->x = b->y * c->z - b->z * c->y;
    a->y = b->z * c->x - b->x * c->z;
    a->z = b->x * c->y - b->y * c->x;

    return 1;
}

/*
 *    Converts a vec3s_t to a string.
 *
 *    @param vec3s_t a    The vector.
 *    @param char   *fmt  The format.
 *
 *    @return char *    The string.
 */
char *vec3_i_to_str(vec3s_t a, char *fmt) {
    static char str[64];

    if (strcmp(fmt, "n,n,n") == 0) {
        sprintf(str, "%d,%d,%d", a.x, a.y, a.z);
    } else if (strcmp(fmt, "n n n") == 0) {
        sprintf(str, "%d %d %d", a.x, a.y, a.z);
    }

    return str;
}

/*
 *    Converts a string to a vec3s_t.
 *
 *    @param char *str    The string.
 *    @param char *fmt    The format.
 * 
 *    @return vec3s_t    The vector.
 */
vec3s_t str_to_vec3_i(char *str, char *fmt) {
    vec3s_t v = {0, 0, 0};

    if (strcmp(fmt, "n,n,n") == 0) {
        sscanf(str, "%d,%d,%d", &v.x, &v.y, &v.z);
    } else if (strcmp(fmt, "n n n") == 0) {
        sscanf(str, "%d %d %d", &v.x, &v.y, &v.z);
    }

    return v;
}

/*
 *    Converts a list of strings to a string.
 *
 *    @param char **str    The list of strings.
 *    @param int    len    The length of the list.
 *    @param char   *fmt   The format.
 *
 *    @return char *    The string.
 */
char *str_list_to_str(char **str, int len, char *fmt) {
    static char s[1024];
    int         i;

    s[0] = '\0';

    if (strcmp(fmt, "'n','n','n'") == 0) {
        for (i = 0; i < len; i++) {
            strcat(s, "\"");
            strcat(s, str[i]);
            strcat(s, "\"");
            if (i < len - 1) {
                strcat(s, ",");
            }
        }
    }

    return s;

}

/*
 *    Converts a string to a list of strings.
 *
 *    @param char   *str    The string.
 *    @param int     len    The length of the list.
 *    @param char   *fmt    The format.
 *
 *    @return char **    The list of strings.
 */
char **str_to_str_list(char *str, int len, char *fmt) {
    char **s = (char **)malloc(len * sizeof(char *));
    int    i;

    if (strcmp(fmt, "'n','n','n'") == 0) {
        for (i = 0; i < len; i++) {
            s[i] = (char *)malloc(64 * sizeof(char));
            sscanf(str, "\"%[^\"]\"", s[i]);
            str = strchr(str, ',');
            if (str != NULL) {
                str++;
            }
        }
    }

    return s;
}

/*
 *    Adds a vec4.
 *
 *    @param vec4_t *a    The return vector.
 *    @param vec4_t *b    The first vector.
 *    @param vec4_t *c    The second vector.
 * 
 *    @return unsigned int        The return code.
 */
unsigned int vec4_add(vec4_t *a, vec4_t *b, vec4_t *c) {
    a->w = b->w + c->w;
    a->x = b->x + c->x;
    a->y = b->y + c->y;
    a->z = b->z + c->z;

    return 1;
}

/*
 *    Subtracts a vec4.
 *
 *    @param vec4_t *a    The return vector.
 *    @param vec4_t *b    The first vector.
 *    @param vec4_t *c    The second vector.
 *
 *    @return unsigned int        The return code.
 */
unsigned int vec4_sub(vec4_t *a, vec4_t *b, vec4_t *c) {
    a->w = b->w - c->w;
    a->x = b->x - c->x;
    a->y = b->y - c->y;
    a->z = b->z - c->z;

    return 1;
}

/*
 *    Interpolates a vec4.
 *
 *    @param vec4_t *a    The return vector.
 *    @param vec4_t *b    The first vector.
 *    @param vec4_t *c    The differential.
 *    @param float step     The step.
 *
 *    @return unsigned int        The return code.
 */
unsigned int vec4_interp(vec4_t *a, vec4_t *b, vec4_t *c, float step) {
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
 *    @param float step       The step.
 *
 *    @return unsigned int           The return code.
 */
unsigned int color32_interp(color32_t *a, color32_t *b, color32_t *c, float step) {
    a->r = b->r + c->r * step;
    a->g = b->g + c->g * step;
    a->b = b->b + c->b * step;
    a->a = b->a + c->a * step;

    return 1;
}

/*
 *    Adds a vec.
 *
 *    @param vec_t *ret        The return vector.
 *    @param void *a           The first vector.
 *    @param void *b           The second vector.
 *    @param v_format_e fmt    The vector format.
 * 
 *    @return unsigned int          The return code.
 */
unsigned int vec_add(vec_t *ret, void *a, void *b, v_format_e fmt) {
    switch (fmt) {
    case V_R32G32_F:
        return vec2_add(&ret->v2, (vec2_t *)a, (vec2_t *)b);
    case V_R32G32B32_F:
        return vec3_add(&ret->v3, (vec3_t *)a, (vec3_t *)b);
    case V_R32G32B32A32_F:
        return vec4_add(&ret->v4, (vec4_t *)a, (vec4_t *)b);
    }

    return 0;

}

/*
 *    Subtracts a vec.
 *
 *    @param vec_t *ret        The return vector.
 *    @param void *a           The first vector.
 *    @param void *b           The second vector.
 *    @param v_format_e fmt    The vector format.
 * 
 *    @return unsigned int          The return code.
 */
unsigned int vec_sub(vec_t *ret, void *a, void *b, v_format_e fmt) {
    switch (fmt) {
    case V_R32G32_F:
        return vec2_sub(&ret->v2, (vec2_t *)a, (vec2_t *)b);
    case V_R32G32B32_F:
        return vec3_sub(&ret->v3, (vec3_t *)a, (vec3_t *)b);
    case V_R32G32B32A32_F:
        return vec4_sub(&ret->v4, (vec4_t *)a, (vec4_t *)b);
    }

    return 0;
}

/*
 *    Interpolates a vec.
 *
 *    @param vec_t *ret        The return vector.
 *    @param void *a           The first vector.
 *    @param void *b           The differential.
 *    @param float step          The step.
 *    @param v_format_e fmt    The vector format.
 *
 *    @return unsigned int          The return code.
 */
unsigned int vec_interp(vec_t *ret, void *a, void *b, float step, v_format_e fmt) {
    /*
     *    Some vectors are to be implemented.
     */
    switch (fmt) {
    case V_R8G8B8A8_U:
    case V_R8G8B8A8_S:
        return color32_interp(&ret->c32, (color32_t *)a, (color32_t *)b, step);

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
 *    @param float scale           The scalar.
 *    @param v_format_e fmt      The vector format.
 *
 *    @return unsigned int          The return code.
 */
unsigned int vec_scale(vec_t *ret, void *a, float scale, v_format_e fmt) {
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
 *    @return float          The dot product.
 */
float vec_dot(void *a, void *b, v_format_e fmt) {
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
 *    @return unsigned int           The size of the vertex component in bytes.
 */
unsigned int get_vertex_component_size(v_format_e fmt) {
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
 *    @return float          The length.
 */
float vec_length(void *a, v_format_e fmt) {
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
 *    @return unsigned int          The return code.
 */
unsigned int vec_normalize(void *a, void *b, v_format_e fmt) {
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
 *    @return unsigned int         The return code.
 */
unsigned int plane_from_points(plane_t *a, vec3_t *b, vec3_t *c, vec3_t *d) {
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
 *   @return float             The distance.
 */
float plane_distance(plane_t *a, vec3_t *b) {
    return vec3_dot(&a->normal, b) - a->dist;
}

/*
 *    Swaps the endianness of a 2-byte integer.
 *
 *    @param unsigned short *a    The integer.
 */
void swap_endian16(unsigned short *a) { *a = (*a >> 8) | (*a << 8); }

/*
 *    Swaps the endianness of a 4-byte integer.
 *
 *    @param unsigned int *a    The integer.
 */
void swap_endian32(unsigned int *a) {
    *a = ((*a >> 24) & 0x000000FF) | ((*a >> 8) & 0x0000FF00) |
         ((*a << 8) & 0x00FF0000) | ((*a << 24) & 0xFF000000);
}



/*
 *    Calculates the crc32 of a buffer.
 *
 *    @param void          *buf    The buffer.
 *    @param unsigned long  len    The length of the buffer.
 * 
 *    @return unsigned int         The crc32.
 */
unsigned int calc_crc32(void *buf, unsigned long len) {
    unsigned int crc = 0xFFFFFFFF;
    unsigned char *p = (unsigned char *)buf;

    while (len--) {
        crc = (crc >> 8) ^ _crc32_table[(crc & 0xFF) ^ *p++];
    }

    return crc ^ 0xFFFFFFFF;
}