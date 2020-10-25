#include <keyboardDriver.h>
#include <naiveConsole.h>
#include <lib.h>

#define LEN 58

static char KEYS[] = {
	'?', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '?', '?',
	'?', '?', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '?',
	'?', 'E', '?', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '?',
	'?', '?', '?', '?', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '?', '?',
	'?', '?', '?', '?', ' '
};

static char keyBuffer[1024] = {0};
static int idx = 0;

void keyPressed() {
	char key = getKey();
	if (!(key&0x80) && key < LEN) {
		char c = KEYS[key-1];
		if (c == '?')
			return;

		if (c == 'E') { // Enter
			ncNewline();
		} else {
			keyBuffer[idx++] = c;
		}
	}
}
