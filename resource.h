/*
 *    resource.h    --    header file for hot-swapping resources
 * 
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 * 
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 * 
 *    Included here is a resouce manager that allows for hot-swapping
 *    of resources by using handles.
 */
#pragma once

#include "libchik.h"

#define HANDLE_GET_INDEX( handle )  ( handle & 0xFFFFFFFF )
#define HANDLE_GET_MAGIC( handle )  ( handle >> 32 )

typedef struct {
    mempool_t *apPool;
}resource_t;

/*
 *    Create a new resource manager.
 *
 *    @param  s64           The size of the memory pool to use.
 *
 *    @return resource_t    A pointer to the new resource manager.
 */
resource_t *resource_new( s64 sSize );

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
handle_t resource_add( resource_t *spResource, void *spData, u64 sSize );

/*
 *    Get a resource from the resource manager.
 *
 *    @param  resource_t *        The resource manager to get the resource from.
 *    @param  handle_t            The handle of the resource to get.
 * 
 *    @return void *              The resource.
 *                                Returns NULL if the handle is invalid.
 */
void *resource_get( resource_t *spResource, handle_t sHandle );

/*
 *    Destroy a resource manager.
 *
 *    @param  apResource    The resource manager to destroy.
 */
void resource_destroy( resource_t *spResource );