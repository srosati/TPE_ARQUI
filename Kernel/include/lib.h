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

void saveRegisters();
void saveRip(uint64_t rip);

void getRegisters(uint64_t * buff);

char getKey();

char getChar();

void putChar(char c, uint16_t x, uint16_t y);

TIME getTime();

void getMem(uint64_t mem, uint8_t * buff, uint8_t bytes);

#endif