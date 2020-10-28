#include <exceptions.h>
#include <naiveConsole.h>

#define ZERO_EXCEPTION_ID 0

static void zero_division() {
	ncNewline();
	ncPrint("Zero division exception");
	return;
}

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
}
