/*
 *    mempool_type.h    --    header file for memory pool type
 * 
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 * 
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 * 
 *    Included here is the memory pool type.
 */

#pragma once

#include "types.h"

typedef enum {
    MEMFLAG_FREE = 1 << 0,
    MEMFLAG_USED = 1 << 1,
}memflag_t;

typedef enum {
    MEMERR_NONE,
    MEMERR_NO_MEMORY,
    MEMERR_INVALID_ARG,
    MEMERR_INVALID_SIZE,
    MEMERR_INVALID_POINTER,
}memerror_t;

typedef struct memchunk_s {
    memflag_t          aFlags;
    s8                *apData;
    s64                aSize;

    struct memchunk_s *apNext;
}memchunk_t;

typedef struct {
    s8         *apBuf;
    s8         *apEnd;
    s8         *apCur;
    s64         aSize;

    memchunk_t *apFirst;
}mempool_t;
