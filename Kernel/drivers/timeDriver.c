#include <timeDriver.h>
#include <naiveConsole.h>
#include <stdint.h>

#define TICKS_PER_SECOND 20

static uint64_t ticks = 0;

void timerTick() {
	ticks++;
	//ncPrintDec(ticks);
}

uint64_t getTicks() {
	return ticks;
}

uint64_t getSeconds() {
	return ticks/TICKS_PER_SECOND;
}