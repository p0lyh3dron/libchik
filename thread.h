/*
 *    thread.h    --    header for parallel programming
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on June 18, 2022
 *
 *    Refactored by Karl "p0lyh3dron" Kreuze on January 19, 2023
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file will declare a threadpool that can be used to
 *    submit tasks to be executed in parallel.
 *    Ideally, instructions will be executing all the time to
 *    keep the CPU busy.
 *
 *    In order to do this, some assembly will be required, as C
 *    does not have a standard way of pushing all registers onto
 *    the stack in a manner that could be used to allow for waitless
 *    parallelism.
 */
#ifndef LIBCHIK_THREAD_H
#define LIBCHIK_THREAD_H

#if __unix__
#include <pthread.h>
#else
//#error "Unsupported platform"
#endif /* __unix__  */

/*
 *   Initializes the global threadpool.
 *
 *   @param unsigned long size       The size of the threadpool.
 *   @param unsigned long threads    The number of threads to spawn.
 *
 *   @return int    0 on success, -1 on failure.
 */
int threadpool_init(unsigned long size, unsigned long threads);

/*
 *   Destroys the global threadpool.
 */
void threadpool_destroy(void);

/*
 *   Submits a task to the global threadpool.
 *
 *   @param void *(*fun)(void *)    The function to execute.
 *   @param void *arg               The argument to pass to the function.
 *
 *   @return int    0 on success, -1 on failure.
 */
int threadpool_submit(void *(*fun)(void *), void *arg);

/*
 *   Waits for all tasks to complete.
 */
void threadpool_wait(void);

#endif /* LIBCHIK_THREAD_H  */