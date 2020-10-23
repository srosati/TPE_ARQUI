#ifndef TIME_DRIVER
#define TIME_DRIVER
#include <stdint.h>

void timerTick();

uint64_t getSeconds();

uint64_t getTicks();

#endif