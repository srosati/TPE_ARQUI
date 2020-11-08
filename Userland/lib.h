#ifndef LIB_H
#define LIB_H

#include <stdint.h>

typedef struct {
	uint16_t width;
	uint16_t height;
} SCREEN;

typedef struct {
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} TIME;

void drawPixel(uint16_t x, uint16_t y, uint64_t color);

char getChar();

char putChar(char c, uint16_t x, uint16_t y);

TIME getTime();

SCREEN getScreenDimentions();

uint8_t setInterval(uint16_t ticks, void (*func)(void));

void stopInterval(uint8_t interval);



#endif