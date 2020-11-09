#include <keyboardDriver.h>
#include <stdint.h>
#include <lib.h>

#define LEN 58
#define TO_UPPERCASE 'A' - 'a'
#define BUFF_SIZE 2048

#define SAVE_REGISTERS 80 //Arrow down

typedef struct {
	char buff[BUFF_SIZE];
	unsigned int readPos;
	unsigned int writePos;
} BUFFER;

static char KEYS[] = {
	0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '?',
	'?', '?', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '?',
	'?', '\n', '?', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '?',
	'?', '?', '|', '?', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '?', '?',
	'?', '|', '?', '?', ' '
};

static char shiftPressed = 0;

static BUFFER keyBuffer;

void initKbBuffer() {
	keyBuffer.readPos = 0;
	keyBuffer.writePos = 0;
}

void keyPressed() {
	uint8_t key = getKey();
	if (!(key&0x80) && key < LEN) {
		char c = KEYS[key-1];
		if (c == '?')
			return;

		if (c == '|'){
			shiftPressed = 1;
		} else {
			if (shiftPressed) 
				c += TO_UPPERCASE;

			keyBuffer.buff[keyBuffer.writePos] = c;
			keyBuffer.writePos = (keyBuffer.writePos+1) % BUFF_SIZE;
		}
	} else if (KEYS[(key&0xFF)-0x81] == '|') {
		shiftPressed = 0;
	} else if (key == SAVE_REGISTERS) {
		saveRegisters();
	}
}

int bufferIsEmpty() {
	return keyBuffer.writePos == keyBuffer.readPos;
}

char getNextKey() {
	if (bufferIsEmpty()) return -1;

	int pos = keyBuffer.readPos;
	keyBuffer.readPos = (keyBuffer.readPos+1) % BUFF_SIZE;
	return keyBuffer.buff[pos];
}

