/*
 *    lchik_resource.c    --    source file for hot-swapping resources
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file defines the functions used for loading and unloading
 *    resources.
 */
#include "lchik_resource.h"

#include <string.h>

/*
 *    Create a new resource manager.
 *
 *    @param  long size      The size of the memory pool to use.
 *
 *    @return resource_t    A pointer to the new resource manager.
 */
resource_t *resource_new(long size) {
    resource_t *resource;

    if (size <= 0) {
        LOGF_ERR("Invalid resource manager size.\n");
        return 0;
    }

    resource = malloc(sizeof(resource_t));

    if (resource == 0) {
        LOGF_ERR("Could not allocate memory for resource manager.\n");
        return 0;
    }

    resource->pool = mempool_new(size);

    if (resource->pool == 0) {
        LOGF_ERR("Could not allocate memory for resource manager pool.\n");
        free(resource);
        return 0;
    }

    return resource;
}

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
trap_t resource_add(resource_t *resource, void *data, unsigned long size) {
    unsigned int magic;
    char        *buf;
    trap_t       handle;

    if (resource == 0) {
        LOGF_ERR("Invalid resource manager.\n");
        return INVALID_TRAP;
    }

    if (data == 0) {
        LOGF_ERR("Invalid resource data.\n");
        return INVALID_TRAP;
    }

    if (size <= 0) {
        LOGF_ERR("Invalid resource size.\n");
        return INVALID_TRAP;
    }

    magic = rand();

    buf = mempool_alloc(resource->pool, size + sizeof(magic));
    if (buf == nullptr) {
        LOGF_ERR("Could not allocate memory for resource.\n");
        return INVALID_TRAP;
    }

    /*
     *    Copy the magic number followed by the data.
     */
    memcpy(buf, &magic, sizeof(magic));
    memcpy(buf + sizeof(magic), data, size);

    handle.index = buf - resource->pool->buf;
    handle.magic = magic;
    handle.size  = size;

    return handle;
}

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
void *resource_get(resource_t *resource, trap_t handle) {
    unsigned int magic;
    char        *buf;

    if (resource == 0) {
        LOGF_ERR("Invalid resource manager.\n");
        return 0;
    }

    if (BAD_TRAP(handle)) {
        LOGF_ERR("Invalid resource handle.\n");
        return 0;
    }

    if (handle.index >= resource->pool->len) {
        LOGF_ERR("Invalid resource index.\n");
        return 0;
    }

    buf   = resource->pool->buf + handle.index;
    magic = *(unsigned int *)buf;

    if (handle.magic != magic) {
        LOGF_ERR("Invalid resource magic.\n");
        return 0;
    }

    return buf + sizeof(magic);
}

/*
 *    Remove a resource from the resource manager.
 *
 *    @param  resource_t *resource        The resource manager to remove the
 * resource from.
 *    @param  trap_t handle               The handle of the resource to remove.
 */
void resource_remove(resource_t *resource, trap_t handle) {
    unsigned int index;
    unsigned int magic;
    char        *buf;

    if (resource == 0) {
        LOGF_ERR("Invalid resource manager.\n");
        return;
    }

    if (BAD_TRAP(handle)) {
        LOGF_ERR("Invalid resource handle.\n");
        return;
    }

    index = handle.index;
    magic = handle.magic;

    if (index >= resource->pool->len) {
        LOGF_ERR("Invalid resource index.\n");
        return;
    }

    buf = resource->pool->buf + index;

    if (*(unsigned int *)buf != magic) {
        LOGF_ERR("Invalid resource magic.\n");
        return;
    }

    mempool_free(resource->pool, buf);
}

/*
 *    Destroy a resource manager.
 *
 *    @param resource_t *resource    The resource manager to destroy.
 */
void resource_destroy(resource_t *resource) {
    if (resource == 0) {
        LOGF_ERR("Invalid resource manager.\n");
        return;
    }

    mempool_destroy(resource->pool);
    free(resource);
}