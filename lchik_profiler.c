/*
 *    lchik_profiler.c    --    source for profiling.
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on January 8, 2024
 *
 *    This file is part of the Chik library, a general purpose
 *    library for the Chik engine and her games.
 *
 *    This file defines the profiler, which is used to 
 *    label a section of code and measure its performance.
 */
#include "lchik_profiler.h"

#include "lchik_log.h"

_profiled_t _profiled[_CHIK_PROFILER_MAX_PROFILED];

_profiled_stack_t *_profiled_stack = (_profiled_stack_t *)0x0;

/*
 *    Initializes the profiler.
 *    This function must be called before any other profiler functions.
 */
void chik_profiler_init() {
#if 0
    for (unsigned long i = 0; i < _CHIK_PROFILER_MAX_PROFILED; ++i) {
        _profiled[i].name          = (char *)0x0;
        _profiled[i].calls         = 0;
        _profiled[i].total_time_s  = 0;
        _profiled[i].total_time_ns = 0;
    }

    chik_profiler_begin("Chik Engine");
#endif
}

/*
 *    Begins profiling a function.
 *
 *    @param name    The name of the profiled region.
 */
void chik_profiler_begin(const char *name) {
#if 0
    if (_profiled_stack == (_profiled_stack_t *)0x0) {
        _profiled_stack = (_profiled_stack_t *)malloc(sizeof(_profiled_stack_t));

        _profiled_stack->name = name;
        _profiled_stack->next = (_profiled_stack_t *)0x0;
    } else {
        _profiled_stack_t *new_stack = (_profiled_stack_t *)malloc(sizeof(_profiled_stack_t));

        new_stack->name = name;
        new_stack->next = _profiled_stack;

        _profiled_stack = new_stack;
    }

    for (unsigned long i = 0; i < _CHIK_PROFILER_MAX_PROFILED; ++i) {
        if (_profiled[i].name != (char *)0x0 && strcmp(_profiled[i].name, name) == 0) {
            ++_profiled[i].calls;

            clock_gettime(CLOCK_MONOTONIC, &_profiled[i].start);

            return;
        }

        if (_profiled[i].name == (char *)0x0) {
            _profiled[i].name = name;
            ++_profiled[i].calls;
            
            clock_gettime(CLOCK_MONOTONIC, &_profiled[i].start);

            return;
        }
    }

    VLOGF_ERR("Could not profile %s: too many profiled regions.", name);
#endif
}

/*
 *    Ends profiling a function.
 */
void chik_profiler_end() {
#if 0
    if (_profiled_stack == (_profiled_stack_t *)0x0) {
        LOGF_ERR("No profiler stack.");
        return;
    }

    for (unsigned long i = 0; i < _CHIK_PROFILER_MAX_PROFILED; ++i) {
        if (_profiled[i].name != (char *)0x0 && strcmp(_profiled[i].name, _profiled_stack->name) == 0) {
            clock_gettime(CLOCK_MONOTONIC, &_profiled[i].end);

            _profiled[i].total_time_s  += _profiled[i].end.tv_sec  - _profiled[i].start.tv_sec;
            _profiled[i].total_time_ns += _profiled[i].end.tv_nsec - _profiled[i].start.tv_nsec;

            if (_profiled[i].total_time_ns > 1000000000) {
                _profiled[i].total_time_s  += 1;
                _profiled[i].total_time_ns %= 1000000000;
            }

            _profiled_stack_t *old_stack = _profiled_stack;

            _profiled_stack = _profiled_stack->next;

            free(old_stack);

            return;
        }
    }
#endif
}

/*
 *    Ends the profiler.
 */
void chik_profiler_exit() {
#if 0
    chik_profiler_end();

    for (unsigned long i = 0; i < _CHIK_PROFILER_MAX_PROFILED; ++i) {
        if (_profiled[i].name != (char *)0x0) {
            VLOGF_MSG("%s: %lu calls, %lu.%lu seconds.", _profiled[i].name, _profiled[i].calls, _profiled[i].total_time_s, _profiled[i].total_time_ns);
        }
    }
#endif
}