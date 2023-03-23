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

#define INVALID_INDEX (unsigned int)0xFFFFFFFF
#define INVALID_TRAP \
    (trap_t) { .index = INVALID_INDEX, .magic = 0, .size = 0 }
#define BAD_TRAP(handle) (handle.index == INVALID_INDEX)

typedef struct {
    mempool_t *pool;
} resource_t;

/*
 *    Create a new resource manager.
 *
 *    @param  long size      The size of the memory pool to use.
 *
 *    @return resource_t    A pointer to the new resource manager.
 */
resource_t *resource_new(long size);

/*
 *    Add a resource to the resource manager.
 *
 *    @param  resource_t *resource        The resource manager to add the
 * resource to.
 *    @param  void *data                  The resource to add.
 *    @param  unsigned long size                    The size of the resource to add.
 *
 *    @return trap_t                 The handle of the resource.
 *                                     If the resource manager is full,
 *                                     this will be 0.
 */
trap_t resource_add(resource_t *resource, void *data, unsigned long size);

/*
 *    Get a resource from the resource manager.
 *
 *    @param  resource_t *resource        The resource manager to get the
 * resource from.
 *    @param  trap_t handle               The handle of the resource to get.
 *
 *    @return void *              The resource.
 *                                Returns NULL if the handle is invalid.
 */
void *resource_get(resource_t *resource, trap_t handle);

/*
 *    Remove a resource from the resource manager.
 *
 *    @param  resource_t *resource        The resource manager to remove the
 * resource from.
 *    @param  trap_t handle               The handle of the resource to remove.
 */
void resource_remove(resource_t *resource, trap_t handle);

/*
 *    Destroy a resource manager.
 *
 *    @param resource_t *resource    The resource manager to destroy.
 */
void resource_destroy(resource_t *resource);