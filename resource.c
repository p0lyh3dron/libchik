/*
 *    resource.c    --    source file for hot-swapping resources
 * 
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 * 
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 * 
 *    This file defines the functions used for loading and unloading
 *    resources.
 */
#include "resource.h"

#include <string.h>

/*
 *    Create a new resource manager.
 *
 *    @param  s64           The size of the memory pool to use.
 *
 *    @return resource_t    A pointer to the new resource manager.
 */
resource_t *resource_new( s64 sSize ) {
    if ( sSize <= 0 ) {
        log_error( "Invalid resource manager size." );
        return 0;
    }

    resource_t *pResource = malloc( sizeof( resource_t ) );

    if( pResource == 0 ) {
        log_error( "Could not allocate memory for resource manager." );
        return 0;
    }

    pResource->apPool = mempool_new( sSize );

    if( pResource->apPool == 0 ) {
        log_error( "Could not allocate memory for resource manager pool." );
        free( pResource );
        return 0;
    }

    return pResource;
}

/*
 *    Add a resource to the resource manager.
 *
 *    @param  resource_t *        The resource manager to add the resource to.
 *    @param  void *              The resource to add.
 *    @param  u64                 The size of the resource to add.
 * 
 *    @return handle_t                 The handle of the resource.
 *                                     If the resource manager is full,
 *                                     this will be 0.
 */
handle_t resource_add( resource_t *spResource, void *spData, u64 sSize ) {
    if( spResource == 0 ) {
        log_error( "Invalid resource manager." );
        return 0;
    }

    if( spData == 0 ) {
        log_error( "Invalid resource data." );
        return 0;
    }

    if( sSize <= 0 ) {
        log_error( "Invalid resource size." );
        return 0;
    }

    u32 magic = rand();

    s8 *pBuf = mempool_alloc( spResource->apPool, sSize + sizeof( magic ) );
    if ( pBuf == 0 ) {
        log_error( "Could not allocate memory for resource." );
        return 0;
    }

    /*
     *    Copy the magic number followed by the data.
     */
    memcpy( pBuf, &magic, sizeof( magic ) );
    memcpy( pBuf + sizeof( magic ), spData, sSize );

    handle_t handle = ( pBuf - spResource->apPool->apBuf ) | ( ( u64 )magic << 32 ) | ( ( u128 )sSize << 64 );

    return handle;
}

/*
 *    Get a resource from the resource manager.
 *
 *    @param  resource_t *        The resource manager to get the resource from.
 *    @param  handle_t            The handle of the resource to get.
 * 
 *    @return void *              The resource.
 *                                Returns NULL if the handle is invalid.
 */
void *resource_get( resource_t *spResource, handle_t sHandle ) {
    if( spResource == 0 ) {
        log_error( "Invalid resource manager." );
        return 0;
    }

    if( sHandle == 0 ) {
        log_error( "Invalid resource handle." );
        return 0;
    }

    u32 sIndex = HANDLE_GET_INDEX( sHandle );
    u32 sMagic = HANDLE_GET_MAGIC( sHandle );

    if( sIndex >= spResource->apPool->aSize ) {
        log_error( "Invalid resource index." );
        return 0;
    }

    s8 *pBuf  = spResource->apPool->apBuf + sIndex;
    u32 magic = *( u32 * )pBuf;

    if( magic != sMagic ) {
        log_error( "Invalid resource magic." );
        return 0;
    }

    return pBuf + sizeof( magic );
}

/*
 *    Destroy a resource manager.
 *
 *    @param  apResource    The resource manager to destroy.
 */
void resource_destroy( resource_t *spResource ) {
    if( spResource == 0 ) {
        log_error( "Invalid resource manager." );
        return;
    }

    mempool_destroy( spResource->apPool );
    free( spResource );
}