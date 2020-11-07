#ifndef TIME_DRIVER
#define TIME_DRIVER
#include <stdint.h>

void initTimer();

void timerTick();

uint64_t getSeconds();

uint64_t getTicks();

uint8_t getYear();

uint8_t getMonth();

uint8_t getDay();

uint8_t getHour();

uint8_t getMinute();

uint8_t getSecond();

uint8_t setInterval(uint16_t ticks, void (*func)(void));

void stopInterval(uint8_t interval);

#endif