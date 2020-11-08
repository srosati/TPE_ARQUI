#include <timeDriver.h>
#include <stdint.h>

#define TICKS_PER_SECOND 18

static uint64_t ticks = 0;

typedef struct {
	void (*func)(void);
	uint64_t ticks;
	uint64_t starting_tick;
} INTERVAL;

typedef struct {
	INTERVAL functions[64];
	uint8_t active[64];
	uint8_t size;
} INTERVALS;

static INTERVALS intervals;

uint8_t bcdToInt(uint8_t n) {
	uint8_t d1 = n >> 4;
	uint8_t d2 = n & 0xF;
	return d1*10+d2;
}

void initTimer() {
	intervals.size = 0;
}

void timerTick() {
	ticks++;
	for (int i = 0; i < 10; ++i){
		INTERVAL interval = intervals.functions[i];
		if (intervals.active[i] && (ticks-interval.starting_tick) % interval.ticks == 0) {
			(*(interval.func))();
		}
	}
}

uint64_t getTicks() {
	return ticks;
}

uint64_t getSeconds() {
	return ticks/TICKS_PER_SECOND;
}

uint8_t setInterval(uint16_t ticks, void (*func)(void)) {
	INTERVAL interval;
	interval.ticks = ticks;
	interval.func = func;
	interval.starting_tick = ticks;
	intervals.functions[intervals.size] = interval;
	intervals.active[intervals.size++] = 1;
	return intervals.size-1;
}

void stopInterval(uint8_t idx) {
	if (idx >= 0 && idx < 10) {
		intervals.active[idx] = 0;
	}
}