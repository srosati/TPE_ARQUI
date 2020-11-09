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

void puts(char * str, uint16_t * x, uint16_t * y);

void printf(uint16_t x, uint16_t y, char * format, ...);

uint32_t countDigits(uint32_t num);

void itoa(uint32_t num, char * buff, uint32_t len);

long long atoi(char * str, uint8_t base);

void getMem(uint64_t mem, uint8_t * buff, uint8_t bytes);

void getRegisters(uint64_t * buff);

uint8_t checkException();

void clearScreen();

void invalidOpCode();

#endif