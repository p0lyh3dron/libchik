/*
 *    aqueue.c    --    Source for async queue
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file provides the definition of the async queue functionality.
 */
#include "aqueue.h"

#include "libchik.h"

/*
 *    Creates a new async queue.
 *
 *    @param unsigned long size    The size of the queue.
 *
 *    @return aqueue_t*    A pointer to the new queue.
 */
aqueue_t *aqueue_new(unsigned long size) {
    aqueue_t *queue = (aqueue_t *)malloc(sizeof(aqueue_t));

    if (queue == nullptr) {
        LOGF_ERR("Failed to allocate memory for async queue\n");
        return nullptr;
    }

    queue->tasks = (task_t *)malloc(sizeof(task_t) * size);

    if (queue->tasks == nullptr) {
        LOGF_ERR("Failed to allocate memory for async queue tasks\n");
        free(queue);
        return nullptr;
    }

    queue->size    = size;
    queue->head    = 0;
    queue->tail    = 0;
    queue->count   = 0;
    queue->waiting = 0;

#if __unix__
    if (pthread_mutex_init(&queue->lock, nullptr) != 0) {
        LOGF_ERR("Failed to initialize async queue mutex\n");
        free(queue->tasks);
        free(queue);
        return nullptr;
    }

    if (pthread_cond_init(&queue->cond, nullptr) != 0) {
        LOGF_ERR("Failed to initialize async queue condition variable\n");
        pthread_mutex_destroy(&queue->lock);
        free(queue->tasks);
        free(queue);
        return nullptr;
    }
#else
//#error "Unsupported platform"
#endif /* __unix__  */

    return queue;
}

/*
 *    Destroys an async queue.
 *
 *    @param aqueue_t *queue    The queue to destroy.
 */
void aqueue_destroy(aqueue_t *queue) {
#if __unix__
    pthread_mutex_destroy(&queue->lock);
    pthread_cond_destroy(&queue->cond);
#else
//#error "Unsupported platform"
#endif /* __unix__  */

    free(queue->tasks);
    free(queue);
}

/*
 *    Adds a task to the queue.
 *
 *    @param aqueue_t *queue    The queue to add the task to.
 *    @param task_t   *task     The task to add.
 *
 *    @return int    0 on success, -1 on failure.
 */
int aqueue_add(aqueue_t *queue, task_t *task) {
    task_t *dest;
#if __unix__
    pthread_mutex_lock(&queue->lock);
#else
//#error "Unsupported platform"
#endif /* __unix__  */

    if (queue->count == queue->size) {
#if __unix__
        pthread_mutex_unlock(&queue->lock);
#else
//#error "Unsupported platform"
#endif /* __unix__  */
        return -1;
    }

    dest      = &queue->tasks[queue->tail];
    dest->fun = task->fun;
    dest->arg = task->arg;

    queue->tail = (queue->tail + 1) % queue->size;
    queue->count++;

#if __unix__
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->lock);
#else
//#error "Unsupported platform"
#endif /* __unix__  */

    return 0;
}

/*
 *    Gets a task from the queue.
 *
 *    @param aqueue_t *queue    The queue to get the task from.
 *
 *    @return task_t*    The task.
 */
task_t *aqueue_get(aqueue_t *queue) {
#if __unix__
    pthread_mutex_lock(&queue->lock);
#else
//#error "Unsupported platform"
#endif /* __unix__  */

    queue->waiting++;
    while (queue->count == 0) {
#if __unix__
        pthread_cond_wait(&queue->cond, &queue->lock);
#else
//#error "Unsupported platform"
#endif /* __unix__  */
    }
    queue->waiting--;

    task_t *task = &queue->tasks[queue->head];
    queue->head  = (queue->head + 1) % queue->size;
    queue->count--;

#if __unix__
    pthread_mutex_unlock(&queue->lock);
#else
//#error "Unsupported platform"
#endif /* __unix__  */

    return task;
}

/*
 *    Returns the count of accessors waiting on the queue.
 *
 *    @param aqueue_t *queue    The queue to check.
 *
 *    @return int    The count of accessors waiting on the queue.
 */
int aqueue_waiting(aqueue_t *queue) {
#if __unix__
    pthread_mutex_lock(&queue->lock);
#else
//#error "Unsupported platform"
#endif /* __unix__  */

    int waiting = queue->waiting;

#if __unix__
    pthread_mutex_unlock(&queue->lock);
#else
//#error "Unsupported platform"
#endif /* __unix__  */

    return waiting;
}