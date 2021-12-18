#pragma once

#include <stdbool.h>
//#include <uavohottbridge.h>

/*
struct interrupt_frame{
  uword_t ip;
  uword_t cs;
  uword_t flags;
  uword_t sp;
  uword_t ss;
};
*/

/*
priority of interrupts:
0, 1, 2, 8, 9, 10, 11, 12, 13, 14, 15, 3, 4, 5, 6, 7
*/

/*
TODO:
- implement GDT and IDT
- make space for the interrupt descriptor table
- tell the CPU where that space is
- tell the PIC that you no longer want to use the BIOS defaults
- write a couple of ISR handlers for both IRQs and exceptions
- put the addresses of the ISR handlers in the appropriate descriptors
- enable all supported interrupts in the IRQ mask
*/

//void interrupt_handler(struct interrupt_frame *frame);
bool handle_interrupt(void);
