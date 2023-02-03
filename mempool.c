/*
 *    mempool.c    --    source file for memory pool
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file defines the functions used for allocating and freeing
 *    memory.
 */
#include "mempool.h"

/*
 *    Creates a new memory pool.
 *
 *    @param s64 size            Size of the memory pool in bytes.
 *
 *    @return mempool_t *    Pointer to the new memory pool.
 *                           Returns NULL on failure.
 *                           Should be freed with mempool_free().
 */
mempool_t *mempool_new(s64 size) {
    if (size <= 0) {
        LOGF_ERR("Invalid memory pool size.");
        return 0;
    }

    mempool_t *mempool = malloc(sizeof(mempool_t));

    if (mempool == 0) {
        LOGF_ERR("Could not allocate memory for memory pool.");
        return 0;
    }

    mempool->next = 0;
    mempool->len  = size;
    mempool->buf  = malloc(size);

    if (mempool->buf == 0) {
        LOGF_ERR("Could not allocate memory for memory pool buffer.");
        free(mempool);
        return 0;
    }

    mempool->cur = mempool->buf;
    mempool->end = mempool->buf + size;
    return mempool;
}

/*
 *    Consolidates the memory pool.
 *
 *    @param mempool_t *pool     Pointer to the memory pool.
 *
 *    @return memerror_t     Error code.
 */
memerror_t mempool_consolidate(mempool_t *pool) {
    memchunk_t *chunk;
    memchunk_t *next;

    if (pool == 0) {
        LOGF_ERR("Invalid memory pool.");
        return MEMERR_INVALID_ARG;
    }

    if (pool->next == 0) {
        LOGF_NOTE("Memory pool is free.");
        return MEMERR_NONE;
    }

    for (chunk = pool->next; chunk != 0; chunk = chunk->next) {
        /*
         *    If the current and next chunk are adjacent, merge them.
         */
        if (chunk->flags & MEMFLAG_FREE && chunk->next != 0 &&
            chunk->next->flags & MEMFLAG_FREE) {
            next = chunk->next;
            chunk->len += next->len;
            chunk->next = next->next;

            free(next);
        }
    }
}

/*
 *    Reallocates a memory pool.
 *
 *    @param mempool_t *pool     Pointer to the memory pool.
 *    @param s64 size            Size of the memory pool in bytes.
 *
 *    @return memerror_t     Error code.
 *                           MEMERR_NONE on success.
 *                           MEMERR_INVALID_ARG if the memory pool is NULL.
 *                           MEMERR_INVALID_SIZE if the size is <= 0.
 *                           MEMERR_NO_MEMORY if the memory pool could not be
 * allocated.
 */
memerror_t mempool_realloc(mempool_t *pool, s64 size) {
    s8 *buf;

    if (pool == 0) {
        LOGF_ERR("Invalid memory pool.");
        return MEMERR_INVALID_ARG;
    }

    if (size <= 0) {
        LOGF_ERR("Invalid memory pool size.");
        return MEMERR_INVALID_SIZE;
    }

    if (pool->buf == 0) {
        pool->buf = calloc(0, size);

        if (pool->buf == 0) {
            LOGF_ERR("Could not allocate memory for memory pool buffer.");
            return MEMERR_NO_MEMORY;
        }

        pool->cur = pool->buf;
        pool->end = pool->buf + size;
        return MEMERR_NONE;
    }

    buf = realloc(pool->buf, size);

    if (buf == 0) {
        LOGF_ERR("Could not reallocate memory for memory pool buffer.");
        return MEMERR_NO_MEMORY;
    }

    pool->cur = buf + (pool->cur - pool->buf);
    pool->buf = buf;
    pool->end = pool->buf + size;
    pool->len = size;

    return MEMERR_NONE;
}

/*
 *    Allocates a new memory chunk from the memory pool.
 *
 *    @param mempool_t *pool      Pointer to the memory pool.
 *    @param s64 size             Size of the memory chunk in bytes.
 *
 *    @return s8 *           Pointer to the new memory chunk.
 *                           Returns NULL on failure.
 *                           Should be freed with mempool_free().
 *                           The memory chunk is not initialized.
 */
s8 *mempool_alloc(mempool_t *pool, s64 size) {
    memchunk_t *chunk;
    memchunk_t *new;
    memchunk_t *last;
    char       *buf;

    if (pool == 0) {
        LOGF_ERR("Invalid memory pool.");
        return 0;
    }

    if (size <= 0) {
        LOGF_ERR("Invalid memory chunk size.");
        return 0;
    }

    /*
     *    Check for free chunks.
     */
    for (memchunk_t *chunk = pool->next; chunk != 0; chunk = chunk->next) {
        if (chunk->flags & MEMFLAG_FREE && chunk->len >= size) {
            /*
             *    Split the chunk if it's too big.
             */
            if (chunk->len > size) {
                new         = (memchunk_t *)calloc(0, sizeof(memchunk_t));
                new->flags  = MEMFLAG_USED;
                new->len    = chunk->len - size;
                new->next   = chunk->next;
                chunk->next = new;
            }
            chunk->flags = MEMFLAG_USED;
            chunk->len   = size;
            return chunk->data;
        }
    }
    /*
     *    No free chunks, check if there's enough space.
     */
    if (pool->cur + size > pool->end) {
        LOGF_ERR("Not enough memory in memory pool.");
        return 0;
    }

    /*
     *    Allocate a new chunk.
     */
    new        = (memchunk_t *)malloc(sizeof(memchunk_t));
    buf        = pool->cur;
    new->flags = MEMFLAG_USED;
    new->len   = size;
    new->data  = pool->cur;
    new->next  = 0;
    pool->cur += size;

    /*
     *    Add the chunk to the list.
     */
    if (pool->next == 0) {
        pool->next = new;
    } else {
        last = pool->next;
        while (last->next != 0) {
            last = last->next;
        }
        last->next = new;
    }

    return buf;
}

/*
 *    Frees a memory chunk from the memory pool.
 *
 *    @param mempool_t *pool      Pointer to the memory pool.
 *    @param s8 *data             Pointer to the memory chunk.
 */
void mempool_free(mempool_t *pool, s8 *data) {
    memchunk_t *chunk;

    if (pool == 0) {
        LOGF_ERR("Invalid memory pool.\n");
        return;
    }

    if (chunk == 0) {
        LOGF_ERR("Invalid memory chunk.\n");
        return;
    }

    /*
     *    Find the chunk.
     */
    chunk = pool->next;
    while (chunk != 0) {
        if (chunk->data == data) {
            break;
        }
        chunk = chunk->next;
    }

    if (chunk->data != data) {
        LOGF_ERR("Could not find memory chunk.\n");
        return;
    }

    /*
     *    Free the chunk.
     */
    chunk->flags = MEMFLAG_FREE;
}

/*
 *    Destroys a memory pool.
 *
 *    @param mempool_t *pool     Pointer to the memory pool to destroy.
 *
 *    @return void
 */
void mempool_destroy(mempool_t *pool) {
    memchunk_t *chunk;
    memchunk_t *next;

    if (pool == 0) {
        LOGF_ERR("Invalid memory pool.");
        return;
    }

    if (pool->buf != 0) {
        free(pool->buf);
    }

    chunk = pool->next;
    while (chunk != 0) {
        next = chunk->next;
        free(chunk);
        chunk = next;
    }

    free(pool);
}