#include <keyboardDriver.h>
#include <naiveConsole.h>



void keyPressed() {
	char key = getKey();
	if (!(key&0x80)) {
		ncPrint("Key pressed: ");
		ncPrintHex(key);
	}
}