#include <stdint.h>
#include <idtLoader.h>
#include <defs.h>
#include <interrupts.h>
#include <exceptions.h>
#include <timeDriver.h>

#pragma pack(push)		/* Push de la alineación actual */
#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */

/* Descriptor de interrupcion */
typedef struct {
  uint16_t offset_l, selector;
  uint8_t cero, access;
  uint16_t offset_m;
  uint32_t offset_h, other_cero;
} DESCR_INT;

#pragma pack(pop)		/* Reestablece la alinceación actual */

DESCR_INT * idt = (DESCR_INT *) 0;	// IDT de 255 entradas

static void setupIDTEntry (int index, uint64_t offset) {
  idt[index].selector = 0x08;
  idt[index].offset_l = offset & 0xFFFF;
  idt[index].offset_m = (offset >> 16) & 0xFFFF;
  idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
  idt[index].access = ACS_INT;
  idt[index].cero = 0;
  idt[index].other_cero = (uint64_t) 0;
}

void configureIDT() {
  _cli();

  setupIDTEntry(0x20, (uint64_t)&_irq0handler); // Timer
  setupIDTEntry(0x21, (uint64_t)&_irq1handler); // Keyboard

  setupIDTEntry(0x00, (uint64_t)&_exception0Handler);
  setupIDTEntry(0x01, (uint64_t)&_exception1Handler);

	//Solo interrupcion timer tick y teclado habilitadas
	picMasterMask(0xFC); //1111 1100
	picSlaveMask(0xFF);
        
	_sti();
}

