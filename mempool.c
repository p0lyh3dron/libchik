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
 *    @param s64             Size of the memory pool in bytes.
 * 
 *    @return mempool_t *    Pointer to the new memory pool.
 *                           Returns NULL on failure.
 *                           Should be freed with mempool_free().
 */
mempool_t *mempool_new( s64 sSize ) {
    if ( sSize <= 0 ) {
        log_error( "Invalid memory pool size." );
        return 0;
    }

    mempool_t *pMempool = malloc( sizeof( mempool_t ) );

    if( pMempool == 0 ) {
        log_error( "Could not allocate memory for memory pool." );
        return 0;
    }

    pMempool->apFirst = 0;
    pMempool->aSize   = sSize;
    pMempool->apBuf   = malloc( sSize );

    if( pMempool->apBuf == 0 ) {
        log_error( "Could not allocate memory for memory pool buffer." );
        free( pMempool );
        return 0;
    }

    pMempool->apCur = pMempool->apBuf;
    pMempool->apEnd = pMempool->apBuf + sSize;
    return pMempool;
}

/*
 *    Consolidates the memory pool.
 *
 *    @param mempool_t *     Pointer to the memory pool.
 * 
 *    @return memerror_t     Error code.
 */
memerror_t mempool_consolidate( mempool_t *spPool ) {
    if( spPool == 0 ) {
        log_error( "Invalid memory pool." );
        return MEMERR_INVALID_ARG;
    }

    if ( spPool->apFirst == 0 ) {
        log_note( "Memory pool is free." );
        return MEMERR_NONE;
    }

    for ( memchunk_t *pChunk = spPool->apFirst; pChunk != 0; pChunk = pChunk->apNext ) {
        /*
         *    If the current and next chunk are adjacent, merge them.
         */
        if ( pChunk->aFlags & MEMFLAG_FREE && pChunk->apNext != 0 && pChunk->apNext->aFlags & MEMFLAG_FREE ) {
            memchunk_t *pNext = pChunk->apNext;
            pChunk->aSize    += pNext->aSize;
            pChunk->apNext    = pNext->apNext;

            free( pNext );
        }
    }
}

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
memerror_t mempool_realloc( mempool_t *spPool, s64 sSize ) {
    if ( spPool == 0 ) {
        log_error( "Invalid memory pool." );
        return MEMERR_INVALID_ARG;
    }

    if ( sSize <= 0 ) {
        log_error( "Invalid memory pool size." );
        return MEMERR_INVALID_SIZE;
    }

    if ( spPool->apBuf == 0 ) {
        spPool->apBuf = calloc( 0, sSize );

        if ( spPool->apBuf == 0 ) {
            log_error( "Could not allocate memory for memory pool buffer." );
            return MEMERR_NO_MEMORY;
        }

        spPool->apCur = spPool->apBuf;
        spPool->apEnd = spPool->apBuf + sSize;
        return MEMERR_NONE;
    }

    s8 *pBuf = realloc( spPool->apBuf, sSize );
    
    if ( pBuf == 0 ) {
        log_error( "Could not reallocate memory for memory pool buffer." );
        return MEMERR_NO_MEMORY;
    }

    spPool->apCur = pBuf + ( spPool->apCur - spPool->apBuf );
    spPool->apBuf = pBuf;
    spPool->apEnd = spPool->apBuf + sSize;
    spPool->aSize = sSize;

    return MEMERR_NONE;
}

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
s8 *mempool_alloc( mempool_t *spPool, s64 sSize ) {
    if ( spPool == 0 ) {
        log_error( "Invalid memory pool." );
        return 0;
    }

    if ( sSize <= 0 ) {
        log_error( "Invalid memory chunk size." );
        return 0;
    }

    /*
     *    Check for free chunks.
     */
    for ( memchunk_t *pChunk = spPool->apFirst; pChunk != 0; pChunk = pChunk->apNext ) {
        if ( pChunk->aFlags & MEMFLAG_FREE && pChunk->aSize >= sSize ) {
            /*
             *    Split the chunk if it's too big.
             */
            if ( pChunk->aSize > sSize ) {
                memchunk_t *pNew = ( memchunk_t* )calloc( 0, sizeof( memchunk_t ) );
                pNew->aFlags   = MEMFLAG_USED;
                pNew->aSize    = pChunk->aSize - sSize;
                pNew->apNext   = pChunk->apNext;
                pChunk->apNext = pNew;
            }
            pChunk->aFlags = MEMFLAG_USED;
            pChunk->aSize = sSize;
            return pChunk->apData;
        }
    }
    /*
     *    No free chunks, check if there's enough space.
     */
    if ( spPool->apCur + sSize > spPool->apEnd ) {
        log_error( "Not enough memory in memory pool." );
        return 0;
    }

    /*
     *    Allocate a new chunk.
     */
    memchunk_t *pChunk = ( memchunk_t* )malloc( sizeof( memchunk_t ) );
    pChunk->aFlags  = MEMFLAG_USED;
    pChunk->aSize   = sSize;
    pChunk->apData  = spPool->apCur;
    pChunk->apNext  = 0;
    spPool->apCur  += sSize;

    /*
     *    Add the chunk to the list.
     */
    if ( spPool->apFirst == 0 ) {
        spPool->apFirst = pChunk;
    } else {
        memchunk_t *pLast = spPool->apFirst;
        while ( pLast->apNext != 0 ) {
            pLast = pLast->apNext;
        }
        pLast->apNext = pChunk;
    }

    s8 *pBuf       = spPool->apCur;
    spPool->apCur += sSize;
    return pBuf;
}

/*
 *    Frees a memory chunk from the memory pool.
 *
 *    @param mempool_t *     Pointer to the memory pool.
 *    @param s8 *            Pointer to the memory chunk.
 */
void mempool_free( mempool_t *spPool, s8 *spChunk ) {
    if ( spPool == 0 ) {
        log_error( "Invalid memory pool." );
        return;
    }

    if ( spChunk == 0 ) {
        log_error( "Invalid memory chunk." );
        return;
    }

    /*
     *    Find the chunk.
     */
    memchunk_t *pChunk = spPool->apFirst;
    while ( pChunk != 0 ) {
        if ( pChunk->apData == spChunk ) {
            break;
        }
        pChunk = pChunk->apNext;
    }

    if ( pChunk->apData != spChunk ) {
        log_error( "Could not find memory chunk." );
        return;
    }

    /*
     *    Free the chunk.
     */
    pChunk->aFlags = MEMFLAG_FREE;
}

/*
 *    Destroys a memory pool.
 *
 *    @param mempool_t *     Pointer to the memory pool to destroy.
 * 
 *    @return void
 */
void mempool_destroy( mempool_t *spPool ) {
    if ( spPool == 0 ) {
        log_error( "Invalid memory pool." );
        return;
    }

    if ( spPool->apBuf != 0 ) {
        free( spPool->apBuf );
    }

    memchunk_t *pChunk = spPool->apFirst;
    while ( pChunk != 0 ) {
        memchunk_t *pNext = pChunk->apNext;
        free( pChunk );
        pChunk = pNext;
    }
    
    free( spPool );
}