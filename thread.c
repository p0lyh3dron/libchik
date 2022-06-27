/*
 *    thread.c    --    source for parallel programming
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on June 18, 2022
 * 
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 * 
 *    This file will defines the functions for creating and manipulating threads.
 */
#include "thread.h"

#if __unix__
    #include <unistd.h>
#elif _WIN32
    #include <windows.h>
#endif /* __unix__  */

threadpool_t gThreadpool;

pthread_mutex_t gMutex;

/*
 *    Thread subrountine.
 */
void *thread_routine( void *spArg ) {
    thread_t *pThread = ( thread_t * )spArg;
    while ( pThread->aFlags & LIBCHIK_THREAD_FLAG_RUNNING ) {
        /*
         *    Look for a task to run.
         */
        pthread_mutex_lock( &gMutex );
        s64 i;
        for ( i = 0; i < LIBCHIK_THREAD_MAX_TASKS; ++i ) {
            if ( pThread->aTasks[ i ].aFlags & LIBCHIK_TASK_FLAG_PENDING ) {
                break;
            }
        }
        pthread_mutex_unlock( &gMutex );

        if ( i != LIBCHIK_THREAD_MAX_TASKS ) {
            /*
             *    Run the task.
             */
            pThread->aTasks[ i ].aFlags &= ~LIBCHIK_TASK_FLAG_PENDING;
            pThread->aTasks[ i ].aFlags |= LIBCHIK_TASK_FLAG_RUNNING;
            pThread->aTasks[ i ].apFunc( pThread->aTasks[ i ].apArgs );

            /*
             *    Mark the task as finished.
             */
            pthread_mutex_lock( &gMutex );
            pThread->aTasks[ i ].aFlags &= ~LIBCHIK_TASK_FLAG_RUNNING;
            pThread->aTasks[ i ].aFlags |= LIBCHIK_TASK_FLAG_NONE;
            pThread->aNumTasks--;
            pthread_mutex_unlock( &gMutex );
        }
        /*
         *    If there are no tasks to run, sleep.
         */
        else {
#if __unix__
            usleep( 1 );
#elif _WIN32
            Sleep( 1 );
#endif /* __unix__  */
        }
    }
}

/*
 *    Creates a thread.
 */
thread_t thread_create( thread_t *spThread ) {
#if __unix__
    pthread_create( &spThread->aThread, NULL, thread_routine, spThread );
#elif _WIN32
    /*
     *    Implement this.
     */
#endif /* __unix__  */
}

/*
 *    Initializes the global task pool.
 */
void threadpool_init( void ) {
    gThreadpool.aNumThreads = LIBCHIK_THREAD_MAX_THREADS;

    pthread_mutex_init( &gMutex, nullptr );
    
    s64 i;
    for ( i = 0; i < LIBCHIK_THREAD_MAX_THREADS; ++i ) {
        
        gThreadpool.aThreads[ i ].aNumTasks = 0;
        s64 j;
        for ( j = 0; j < LIBCHIK_THREAD_MAX_TASKS; ++j ) {
            gThreadpool.aThreads[ i ].aTasks[ j ].aFlags  = LIBCHIK_TASK_FLAG_NONE;
            gThreadpool.aThreads[ i ].aTasks[ j ].apFunc  = nullptr;

            gThreadpool.aThreads[ i ].aFlags = LIBCHIK_THREAD_FLAG_RUNNING;
        }
        /* 
         *    Launch the thread.
         */
        thread_create( &gThreadpool.aThreads[ i ] );
    }
}

/*
 *    Adds a task to the global task pool.
 */
void threadpool_add_task( void ( *spFunc )( void * ), void *spArg, u32 sArgsLen ) {
    pthread_mutex_lock( &gMutex );
    s64 i;
    u32 freeTasks     = 0;
    u32 threadId      = 0;
    for ( i = 0; i < LIBCHIK_THREAD_MAX_THREADS; ++i ) {
        if ( gThreadpool.aThreads[ i ].aNumTasks > freeTasks ) {
            freeTasks = gThreadpool.aThreads[ i ].aNumTasks;
            threadId = i;
        }
    }
    /*
     *    Add the task to the thread.
     */
    for ( i = 0; i < LIBCHIK_THREAD_MAX_TASKS; ++i ) {
        if ( gThreadpool.aThreads[ threadId ].aTasks[ i ].aFlags == LIBCHIK_TASK_FLAG_NONE ) {
            gThreadpool.aThreads[ threadId ].aNumTasks++;
            gThreadpool.aThreads[ threadId ].aTasks[ i ].apFunc = spFunc;
            memcpy( gThreadpool.aThreads[ threadId ].aTasks[ i ].apArgs, spArg, sArgsLen );
            gThreadpool.aThreads[ threadId ].aTasks[ i ].aFlags = LIBCHIK_TASK_FLAG_PENDING;
            break;
        }
    }
    pthread_mutex_unlock( &gMutex );
}

/*
 *    Waits for all tasks to finish.
 */
void threadpool_wait( void ) {
    s64 i;
    for ( i = 0; i < LIBCHIK_THREAD_MAX_THREADS; ++i ) {
        while ( gThreadpool.aThreads[ i ].aNumTasks > 0 ) {
            /*
             *    Wait for the thread to finish.
             */
        }
    }
}