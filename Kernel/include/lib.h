#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char * cpuVendor(char *result);

void _sti();
void _cli();

void picMasterMask(uint8_t);
void picSlaveMask(uint8_t);

void _irq0handler();
void _irq1handler();

char getKey();

#endif