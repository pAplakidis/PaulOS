#pragma once
#include <stdbool.h>

#include "interrupt_descriptor_table.h"

/*
#include <uavohottbridge.h>

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

struct interrupt_frame{
  uint16_t ip;
  uint16_t  cs;
  uint16_t  flags;
  uint16_t  sp;
  uint16_t  ss;
};

//void interrupt_handler(struct interrupt_frame *frame);
void prepare_interrupts();
bool handle_interrupt(void);
__attribute__((interrupt))
void page_fault_handler(struct interrupt_frame* frame);
