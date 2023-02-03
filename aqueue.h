/*
 *    aqueue.h    --    Header for async queue
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on March 20, 2022
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file provides the declaration for an async queue.
 */
#ifndef CHIK_AQUEUE_H
#define CHIK_AQUEUE_H

#if __unix__
#include <pthread.h>
#else
#error "Unsupported platform"
#endif /* __unix__  */

typedef struct {
    void *(*fun)(void *);
    void *arg;
} task_t;

typedef struct {
    task_t       *tasks;
    unsigned long size;
    unsigned long head;
    unsigned long tail;
    unsigned long count;
    unsigned long waiting;
#if __unix__
    pthread_mutex_t lock;
    pthread_cond_t  cond;
#else
#error "Unsupported platform"
#endif /* __unix__  */
} aqueue_t;

/*
 *    Creates a new async queue.
 *
 *    @param unsigned long size    The size of the queue.
 *
 *    @return aqueue_t*    A pointer to the new queue.
 */
aqueue_t *aqueue_new(unsigned long size);

/*
 *    Destroys an async queue.
 *
 *    @param aqueue_t *queue    The queue to destroy.
 */
void aqueue_destroy(aqueue_t *queue);

/*
 *    Adds a task to the queue.
 *
 *    @param aqueue_t *queue    The queue to add the task to.
 *    @param task_t   *task     The task to add.
 *
 *    @return int    0 on success, -1 on failure.
 */
int aqueue_add(aqueue_t *queue, task_t *task);

/*
 *    Gets a task from the queue.
 *
 *    @param aqueue_t *queue    The queue to get the task from.
 *
 *    @return task_t*    The task.
 */
task_t *aqueue_get(aqueue_t *queue);

/*
 *    Returns the count of accessors waiting on the queue.
 *
 *    @param aqueue_t *queue    The queue to check.
 *
 *    @return int    The count of accessors waiting on the queue.
 */
int aqueue_waiting(aqueue_t *queue);

#endif /* CHIK_AQUEUE_H  */