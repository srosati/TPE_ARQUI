/* sampleCodeModule.c */
#include "../lib.h"
#include <stdint.h>
#include <math.h>

typedef int (*EntryPoint)();

#define X_INC 8
#define Y_INC 16

#define LOG_W 255
#define LOG_H 100

static char * regis[17] = {"rax","rbx","rcx","rdx","rbp","rsp","rsi","rdi","r8","r9","r10","r11","r12","r13","r14","r15", "rip"};

static SCREEN screen;

static char screenLog[LOG_H][LOG_W];
static uint8_t log_idx = 0;
static uint8_t log_j = 0;

static uint8_t zero = 0;
static uint8_t zeroDiv = 1;

void printScreen() {
	char c;
	for (int i = 0; i <= log_idx; i++) {
		for (int j = 0; j < screen.width/X_INC; ++j) {
			c = screenLog[i][j];
			putChar(c, j * X_INC, screen.height - (log_idx+1-i) * Y_INC);
		}
	}
}

void newLine() {
	log_j = 0;
	log_idx++;
	if (log_idx >= LOG_H) {
		log_idx = LOG_H-1;
		for (int i = 1; i <= log_idx; i++) {
			for (int j = 0; j < LOG_W; ++j)
				screenLog[i-1][j] = screenLog[i][j];
		}
	}
	for (int i = 0; i < screen.width/X_INC; ++i)
		screenLog[log_idx][i] = 0;

	printScreen();
}

void putc(char c) {
	if (log_j >= screen.width/X_INC) 
		newLine();

	screenLog[log_idx][log_j] = c;
	putChar(c, log_j*X_INC, screen.height - Y_INC);
	log_j++;
}

void putcHex(uint8_t hex) {
	if (hex < 0 || hex  > 15){
		putc('M');
		return;
	}

	char c;
	if (hex < 10)
		c = '0' + hex;
	else
		c = 'A' + hex - 10;

	putc(c);
}

void putString(char * str) {
	while(*str) {
		putc(*str);
		str++;
	}
}

void printLine(char * str) {
	putString(str);
	newLine();
}


void readCommand() {
	log_j = 0;
	putc('>');
	putc(' ');
	char c;
	int i;
	for (i = log_j; i < LOG_W; ++i) {
		c = getChar();
		if (c == '\n')
			break;

		putc(c);
		screenLog[log_idx][i] = c;
	}

	for (; i < LOG_W; ++i)
		screenLog[log_idx][i] = 0;

	newLine();
}

uint8_t commandEquals(char * str1, char * str2) {
	while (*str1 && *str2) {
		if (*str1 != *str2)
			return 0;

		str1++;
		str2++;
	}

	return (*str1 == 0 || *str1 == ' ') && *str2 == 0;
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


void printNum(int num, int digits) {
	int len = countDigits(num);
	char aux[len+1];
	itoa(num, aux, len);
	int i;
	for (i = len; i < digits; ++i)
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
	newLine();
}

void printmem(uint64_t mem) {
	uint8_t buff[32];
	getMem(mem, buff, 32);
	putc('0');
	putc('x');
	for (int i = 0; i < 32; i++) {
		uint8_t l = buff[i] >> 4;
		uint8_t r = buff[i] & 0xF;
		putcHex(l);
		putcHex(r);
	}
	newLine();
}

void printRegis(uint64_t regis) {
	putString("0x");
	for (int i = 0; i < 16; ++i) {
		uint8_t v = (regis >> (60 - 4*i)) & 0xF;
		putcHex(v);
	}
}

void inforeg(uint8_t rip) {
	uint64_t registers[17-rip];
	getRegisters(registers);
	for (int i = 0; i < 17-rip; ++i) {
		putString("- ");
		putString(regis[i]);
		putString(": ");
		printRegis(registers[i]);
		newLine();
	}
}

int main() {
	screen = getScreenDimentions();
	clearScreen();
	uint8_t e = checkException();
	if (e == 1) {
		printLine("Zero division exception");
		inforeg(0);
	} else if (e == 2) {
		printLine("Invalid operation code exception");
		inforeg(0);
	}

	while(1) {
		readCommand();
		if (commandEquals(&screenLog[log_idx-1][2], "exit")) {
			break;
		} else if (commandEquals(&screenLog[log_idx-1][2], "help")) {
			printLine("Available commands: ");
			printLine("- help: print available commands");
			printLine("- exit: stop shell");
			printLine("- time: print current time");
			printLine("- inforeg: print registers info");
			printLine("- printmem: print 32 bytes of memory after specified adress");
			printLine("- divZero: cause zero division exception");
			printLine("- invalidOpCode: cause invalid operation code exception");
			printLine("- chess: run chess");
		} else if (commandEquals(&screenLog[log_idx-1][2], "inforeg")) {
			inforeg(1);
		} else if (commandEquals(&screenLog[log_idx-1][2], "printmem")) {
			long long aux;
			if (screenLog[log_idx-1][11] == '0' && screenLog[log_idx-1][12] == 'x')
				aux = atoi(&screenLog[log_idx-1][13], 16);
			else 
				aux = atoi(&screenLog[log_idx-1][11], 10);

			if (aux == -1) {
				printLine("Invalid memory location");
				continue;
			}

			uint64_t mem = aux;
			printmem(mem);
		} else if (commandEquals(&screenLog[log_idx-1][2], "time")) {
			printTime();
		} else if (commandEquals(&screenLog[log_idx-1][2], "chess")) {
			clearScreen();
			int ret = ((EntryPoint) 0x500000)();
			clearScreen();
			if (ret == 0)
				printLine("White won!");
			else if (ret == 1)
				printLine("Black won!");
			else if (ret == 2)
				printLine("Pause");
			else
				printLine("Error");

			printScreen();
		} else if (commandEquals(&screenLog[log_idx-1][2], "zeroDiv")) {
			zeroDiv = 1/zero;
		} else if (commandEquals(&screenLog[log_idx-1][2], "invalidOpCode")) {
			invalidOpCode();
		}
	}
	
	return 0;
}