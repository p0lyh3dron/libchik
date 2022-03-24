/*
 *    mempool.h    --    header file for memory pool
 * 
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 * 
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 * 
 *    Included here is a memory pool, which is a very simple
 *    memory allocator. It is not a general purpose allocator,
 *    but it is a very simple one.
 */
#pragma once

#include "mempool_type.h"

#include "libchik.h"

/*
 *    Creates a new memory pool.
 *
 *    @param s64             Size of the memory pool in bytes.
 * 
 *    @return mempool_t *    Pointer to the new memory pool.
 *                           Returns NULL on failure.
 *                           Should be freed with mempool_free().
 */
mempool_t *mempool_new( s64 sSize );

/*
 *    Consolidates the memory pool.
 *
 *    @param mempool_t *     Pointer to the memory pool.
 * 
 *    @return memerror_t     Error code.
 */
memerror_t mempool_consolidate( mempool_t *spPool );

/*
 *    Reallocates a memory pool.
 *
 *    @param mempool_t *     Pointer to the memory pool.
 *    @param s64             Size of the memory pool in bytes.
 * 
 *    @return memerror_t     Error code.
 *                           MEMERR_NONE on success.
 *                           MEMERR_INVALID_ARG if the memory pool is NULL.
 *                           MEMERR_INVALID_SIZE if the size is <= 0.
 *                           MEMERR_NO_MEMORY if the memory pool could not be allocated.
 */
memerror_t mempool_realloc( mempool_t *spPool, s64 sSize );

/*
 *    Allocates a new memory chunk from the memory pool.
 *
 *    @param mempool_t *     Pointer to the memory pool.
 *    @param s64             Size of the memory chunk in bytes.
 * 
 *    @return s8 *           Pointer to the new memory chunk.
 *                           Returns NULL on failure.
 *                           Should be freed with mempool_free().
 *                           The memory chunk is not initialized.
 */
s8 *mempool_alloc( mempool_t *spPool, s64 sSize );

/*
 *    Frees a memory chunk from the memory pool.
 *
 *    @param mempool_t *     Pointer to the memory pool.
 *    @param s8 *            Pointer to the memory chunk.
 */
void mempool_free( mempool_t *spPool, s8 *spChunk );

/*
 *    Destroys a memory pool.
 *
 *    @param mempool_t *     Pointer to the memory pool to destroy.
 * 
 *    @return void
 */
void mempool_destroy( mempool_t *spPool );