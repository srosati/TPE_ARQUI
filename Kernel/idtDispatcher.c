#include <timeDriver.h>
#include <keyboardDriver.h>
#include <stdint.h>

void irqDispatcher(uint8_t code) {
	switch(code) {
		case 0:
			timerTick();
			break;
		case 1:
			keyPressed();
			break;
	}
}