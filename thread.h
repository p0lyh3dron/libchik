/*
 *    thread.h    --    header for parallel programming
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on June 18, 2022
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

#define LIBCHIK_THREAD_MAX_THREADS 12
#define LIBCHIK_THREAD_MAX_TASKS   8
#define LIBCHIK_THREAD_MAX_ARGUMENT_SIZE 1024

#define LIBCHIK_TASK_FLAG_NONE     0x00
#define LIBCHIK_TASK_FLAG_PENDING  0x01
#define LIBCHIK_TASK_FLAG_RUNNING  0x02
#define LIBCHIK_TASK_FLAG_FINISHED 0x04
#define LIBCHIK_TASK_FLAG_ERROR    0x08

#define LIBCHIK_THREAD_FLAG_NONE    0x00
#define LIBCHIK_THREAD_FLAG_RUNNING 0x01
#define LIBCHIK_THREAD_FLAG_STOP    0x02
#define LIBCHIK_THREAD_FLAG_ERROR   0x04

#include "types.h"

#if __unix__
    #include <pthread.h>
#elif _WIN32    
    #include <windows.h>
#else
    #error "Platform does not support threads."
#endif /* __unix__  */

#if __unix__
    typedef pthread_mutex_t  mutex_t;
#elif _WIN32
    typedef CRITICAL_SECTION mutex_t;
#endif /* __unix__  */

typedef struct {
    u32     aFlags;
    void ( *apFunc )( void * );
    u8      apArgs[ LIBCHIK_THREAD_MAX_ARGUMENT_SIZE ];
} task_t;

typedef struct {
    u32    aFlags;
    task_t aTasks[ LIBCHIK_THREAD_MAX_TASKS ];
    s32    aNumTasks;
#if __unix__
    pthread_t aThread;
#elif _WIN32
    HANDLE aThread;
#endif /* __unix__  */
} thread_t;

typedef struct {
    thread_t aThreads[ LIBCHIK_THREAD_MAX_THREADS ];
    u32      aNumThreads;
} threadpool_t;

/*
 *    Initializes a mutex.
 *
 *    @param mutex_t * The mutex to initialize.
 */
void thread_mutex_init( mutex_t *spMutex );

/*
 *    Unlocks a mutex.
 *
 *    @param mutex_t *    The mutex to unlock.
 */
void thread_mutex_unlock( mutex_t *spMutex );

/*
 *    Locks a mutex.
 *
 *    @param mutex_t *    The mutex to lock.
 */
void thread_mutex_lock( mutex_t *spMutex );

/*
 *    Thread subrountine.
 */
void *thread_routine( void *spArg );

/*
 *    Creates a thread.
 */
thread_t thread_create( thread_t *spThread );

/*
 *    Initializes the global task pool.
 */
void threadpool_init( void );

/*
 *    Adds a task to the global task pool.
 */
void threadpool_add_task( void ( *spFunc )( void * ), void *spArg, u32 sArgsLen );

/*
 *    Waits for all tasks to finish.
 */
void threadpool_wait( void );

#endif /* LIBCHIK_THREAD_H  */