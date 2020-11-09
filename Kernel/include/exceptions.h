#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>

void exceptionDispatcher(int exception);

uint8_t exceptionCode();

void _exception0Handler();

void _exception1Handler();

#endif