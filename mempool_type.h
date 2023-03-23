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
} memflag_t;

typedef enum {
    MEMERR_NONE,
    MEMERR_NO_MEMORY,
    MEMERR_INVALID_ARG,
    MEMERR_INVALID_SIZE,
    MEMERR_INVALID_POINTER,
} memerror_t;

typedef struct memchunk_s {
    memflag_t flags;
    char     *data;
    long      len;

    struct memchunk_s *next;
} memchunk_t;

typedef struct {
    char *buf;
    char *end;
    char *cur;
    long  len;

    memchunk_t *next;
} mempool_t;
