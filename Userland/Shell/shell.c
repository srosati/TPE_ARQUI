/* sampleCodeModule.c */
#include "../lib.h"
#include <stdint.h>
#include <math.h>

typedef int (*EntryPoint)();

#define X_INC 8
#define Y_INC 16

static SCREEN screen;

static uint16_t x = 0;
static uint16_t y = 0;

void putc(char c) {
	if ((x + X_INC) > screen.width) {
		x = 0;
		y += Y_INC;
	}
	putChar(c, x, y);
	x += X_INC;
}

void readCommand(char * str, int len) {
	putc('>');
	putc(' ');
	for (int i = 0; i < len-1; ++i) {
		char c = getChar();
		if (c == '\n') {
			x = 0;
			y += Y_INC;
			break;
		}

		putc(c);
		*str = c;
		str++;
	}
	*str = 0;
}

uint8_t stringEquals(char * str1, char * str2) {
	while (*str1 != 0 && *str2 != 0) {
		if (*str1 != *str2)
			return 0;

		str1++;
		str2++;
	}
	return *str1 == 0 && *str2 == 0;
}

int getLength(int num) {
	if (num == 0) return 1;
	int count = 0;
    while (num) {
        num /= 10;
        ++count;
    }
    return count;
}

int itoa(int num, char * buffer) {
    int curr = 0, k = 0;
    int digits = getLength(num);

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

void printNum(int num, int digits) {
	char aux[4];
	int len = itoa(num, aux);
	int i;
	for (int i = len; i < digits; ++i)
		putc('0');

	for (i = 0; i < len; ++i) 
		putc(aux[i]);
}

void printTime() {
	TIME time = getTime();
	printNum(time.day, 2);
	putc('/');
	printNum(time.month, 2);
	putc('/');
	printNum(time.year, 4);
	putc(' ');
	printNum(time.hour, 2);
	putc(':');
	printNum(time.minute, 2);
	putc(':');
	printNum(time.second, 2);
	x = 0;
	y += Y_INC;
}

int main() {
	screen = getScreenDimentions();
	char command[10];
	while(1) {
		readCommand(command, 10);
		if (stringEquals(command, "exit")) {
			break;
		} else if (stringEquals(command, "help")) {
			/* code */
		} else if (stringEquals(command, "inforeg")) {
			/* code */
		} else if (stringEquals(command, "printmem")) {
			/* code */
		} else if (stringEquals(command, "time")) {
			printTime();
		} else if (stringEquals(command, "chess")) {
			((EntryPoint) 0x500000)();
		}
	}
	
	return 0;
}