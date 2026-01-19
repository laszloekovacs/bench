#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>
#include <stdint.h>

/* performance counting, forward declarations */
void timer_init(void);

// useful for delta calculations
double timer_get_seconds(void);

// performance counter
uint64_t timer_get_nanos(void);

static struct timespec startup_time;

void timer_init(void)
{
    clock_gettime(CLOCK_MONOTONIC, &startup_time);
}

double timer_get_seconds(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now)

        // Calculate difference from startup (optional, keeps numbers smaller)
        // Or just return raw monotonic time converted to double
        double sec = (double)(now.tv_sec - startup_time.tv_sec);
    double nsec = (double)(now.tv_nsec - startup_time.tv_nsec);

    return sec + (nsec * 1e-9);
}

uint64_t timer_get_nanos(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (uint64_t)now.tv_sec * 1000000000ULL + (uint64_t)now.tv_nsec;
}

#endif