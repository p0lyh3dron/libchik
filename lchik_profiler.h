/*
 *    lchik_profiler.h    --    header for profiling.
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on January 8, 2024
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file declares the functions and macros used for profiling.
 */
#ifndef _CHIK_PROFILER_H
#define _CHIK_PROFILER_H

#define _CHIK_PROFILER_MAX_PROFILED 256

#include <time.h>

typedef struct {
    const char     *name;
    unsigned long   calls;
    unsigned long   total_time_s;
    unsigned long   total_time_ns;
    struct timespec start;
    struct timespec end;
} _profiled_t;

typedef struct _profiled_stack_s {
    const char               *name;

    struct _profiled_stack_s *next;
} _profiled_stack_t;

/*
 *    Initializes the profiler.
 *    This function must be called before any other profiler functions.
 */
void chik_profiler_init();

/*
 *    Begins profiling a function.
 *
 *    @param name    The name of the profiled region.
 */
void chik_profiler_begin(const char *name);

/*
 *    Ends profiling a function.
 */
void chik_profiler_end();

/*
 *    Ends the profiler.
 */
void chik_profiler_exit();

#endif /* _CHIK_PROFILER_H  */