#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

void _irq0handler();
void _irq1handler();
void _syscallhandler();

void _sti();
void _cli();

void picMasterMask(uint8_t);
void picSlaveMask(uint8_t);

#endif