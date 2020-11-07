#include <lib.h>
#include <stdint.h>
#include <naiveConsole.h>
#include <timeDriver.h>
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <font.h>
#include <math.h>

void * memset(void * destination, int32_t c, uint64_t length) {
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length) {
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0) {
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	} else {
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

int countDigits(int num) {
	int i = 0;
	while(num != 0) {
		num/=10;
		i++;
	}
	return i;
}

int itoa(int num, char * buffer) {
    int curr = 0, k = 0;
    int digits = countDigits(num);

    if (num == 0) {
        // Base case
        buffer[curr++] = '0';
        buffer[curr] = '\0';
        return 1;
    }

   	if (num < 0) {
   		num *= -1;
   		buffer[0] = '-';
   		digits += 1;
   		k = 1;
   		curr++;
   	}

   	for (int i = digits-1; i >= k; i--) {
   		buffer[i] = (num % 10) + '0';
   		num /= 10;
   	}
   	return digits;
}

void putChar(char c, uint16_t x, uint16_t y) {
	unsigned char * charPixels = charBitmap(c);
	for (int i = 0; i < 16; ++i) {
		char row = *charPixels;
		for (int j = 0; j < 8; ++j) {
			char bit = (row >> (7-j)) & 1;
			uint32_t color = 0;
			if (bit)
				color = 0xFFFFFF;

			drawPixel(x + j, y + i, color);
		}
		charPixels++;
	}
}

char getChar() {
	char c = getNextKey();
	while (c == -1)
		c = getNextKey();

	return c;
}

uint8_t bcdToInt(uint8_t n) {
	uint8_t d1 = n >> 4;
	uint8_t d2 = n & 0xF;
	return d1*10+d2;
}

TIME getTime() {
	TIME time;
	time.year = 2000 + bcdToInt(getYear());
	time.month = bcdToInt(getMonth());
	time.day = bcdToInt(getDay());
	time.hour = bcdToInt(getHour());
	time.minute = bcdToInt(getMinute());
	time.second = bcdToInt(getSecond());
	return time;
}

