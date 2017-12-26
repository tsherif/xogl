#include <time.h>
#include <unistd.h>
#include "utils.h"

double utils_getTime(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1000000.0;
}

void utils_milisleep(double ms) {
    struct timespec ts;
    ts.tv_sec = (time_t) (ms / 1000.0);
    ts.tv_nsec = (long) ((ms - (ts.tv_sec * 1000)) * 1000000);
    nanosleep(&ts, 0);
}
