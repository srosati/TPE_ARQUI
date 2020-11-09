#include "lib.h"
#include <stdarg.h>

void puts(char * str, uint16_t * x, uint16_t * y) {
	while (*str != 0) {
		putChar(*str, *x, *y);
		str++;
		*x += 8;
	}
}

uint32_t countDigits(uint32_t num) {
	int i = 0;
	while (num) {
		num /= 10;
		i++;
	}
	return i;
}

void itoa(uint32_t num, char * buff, uint32_t len) {
	buff[len] = 0;
	for (int i = len-1; i >= 0; i--) {
		buff[i] = '0' + (num%10);
		num /= 10;
	}
}

long long atoi(char * str, uint8_t base) {
	if (base != 10 && base != 16)
		return -1; // Not supported

	int num = 0;
	char c;
	while(*str) {
		c = *str;
		uint8_t digit = c - '0';
		if (c < '0' || c > '9') {
			if (base == 10)
				return -1;

			if ('a' <= c && c <= 'f')
				digit = c - 'a';
			else if ('A' <= c && c <= 'F')
				digit = 10 + c - 'A';
			else
				return -1;
		}

		num *= base;
		num += digit;
		str++;
	}
	return num;
}

void printf(uint16_t x, uint16_t y, char * format, ...) {
	char * rec;
	int i;
	//char * s;

	va_list arg;
    va_start(arg, format);
	for (rec = 0; *rec != 0; ++rec) {
		while(*rec != '%') {
			putChar(*format, x, y);
			x += 8;
			format++;
		}

		rec++;

		switch(*rec) { 
            case 'c' : i = va_arg(arg, int);     //Fetch char argument
                   		putChar(i, x, y);
                   		x += 8;
                        break; 

            case 'd' : i = va_arg(arg, int);         //Fetch Decimal/Integer argument
                        if(i<0) { 
                            i = -i;
                            putChar('-', x, y);
                            x+= 8; 
                        }
                        uint32_t digits = countDigits(i);
                        char n[digits+1];
                        itoa(i, n, digits);
                        puts(n, &x, &y);
                        break;

           /* case 's': s = va_arg(arg, char *);       //Fetch string
                        puts(s, &x, &y); 
                        break;*/
        }   
	}
	va_end(arg);
}