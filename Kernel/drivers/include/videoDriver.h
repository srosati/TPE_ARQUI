#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>

typedef struct {
	uint16_t width;
	uint16_t height;
} SCREEN;

SCREEN getScreenDimentions();

void clearScreen();

void drawPixel(uint16_t x, uint16_t y, uint64_t color);

#endif

