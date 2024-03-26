/*
 *    thread.c    --    source for parallel programming
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on June 18, 2022
 *
 *    Refactored by Karl "p0lyh3dron" Kreuze on January 19, 2023
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file will defines the functions for creating and manipulating
 * threads.
 */
#include "thread.h"

#include <malloc.h>
#include <memory.h>

#include "aqueue.h"

aqueue_t *_threadpool = 0;
int       _threads    = 0;

/*
 *   The thread function.
 *
 *   @param void *arg    The argument to pass to the function.
 *
 *   @return void*    The return value of the function.
 */
void *_threadpool_thread(void *arg) {
    task_t *task;

    while (1) {
        task = aqueue_get(_threadpool);

        if (task == 0)
            break;

        task->fun(task->arg);
    }

    return 0;
}

/*
 *   Initializes the global threadpool.
 *
 *   @param unsigned long size       The size of the threadpool.
 *   @param unsigned long threads    The number of threads to spawn.
 *
 *   @return int    0 on success, -1 on failure.
 */
int threadpool_init(unsigned long size, unsigned long threads) {
    unsigned long i;
#if __unix__
    pthread_t thread;
#endif /* __unix__  */

    _threadpool = aqueue_new(size);
    _threads    = threads;

    if (_threadpool == 0)
        return -1;

    for (i = 0; i < threads; i++) {
#if __unix__
        if (pthread_create(&thread, 0, _threadpool_thread, 0) != 0)
            return -1;
#else
//#error "Unsupported platform"
#endif /* __unix__  */
    }

    return 0;
}

/*
 *   Destroys the global threadpool.
 */
void threadpool_destroy(void) { aqueue_destroy(_threadpool); }

/*
 *   Submits a task to the global threadpool.
 *
 *   @param void *(*fun)(void *)    The function to execute.
 *   @param void *arg               The argument to pass to the function.
 *
 *   @return int    0 on success, -1 on failure.
 */
int threadpool_submit(void *(*fun)(void *), void *arg) {
    task_t task;

    task.fun = fun;
    task.arg = arg;

    return aqueue_add(_threadpool, &task);
}

/*
 *   Waits for all tasks to complete.
 */
void threadpool_wait(void) {
    while (aqueue_waiting(_threadpool) < _threads)
        ;
}