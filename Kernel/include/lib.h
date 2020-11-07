#ifndef LIB_H
#define LIB_H

#include <stdint.h>

typedef struct {
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} TIME;

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char * cpuVendor(char *result);

char getKey();

char getChar();

void putChar(char c, uint16_t x, uint16_t y);

TIME getTime();

#endif