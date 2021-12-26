#pragma once
#include <stdbool.h>

#include "interrupt_descriptor_table.h"

// TODO: complete the codes
// Exception Codes
#define DIV_ZERO_ERROR      0x0
#define DEBUG_EXC           0x1
#define NON_MASKABLE_INT    0x2
/*
#define ERROR      0x3
#define ERROR      0x4
#define ERROR      0x5
#define ERROR      0x6
#define ERROR      0x7
#define ERROR      0x8
#define ERROR      0x9
#define ERROR      0xA
#define ERROR      0xB
#define ERROR      0xC
#define ERROR      0xD
#define ERROR      0xE
#define ERROR      0xF
#define ERROR      0x10
#define ERROR      0x11
#define ERROR      0x12
#define ERROR      0x13
#define ERROR      0x14
#define ERROR      0x15
#define RESERVED            0x16  // TODO: 0x16-0x1b
#define ERROR      0x1C
#define ERROR      0x1D
#define ERROR      0x1E
#define ERROR      0x1F
*/

/*
priority of interrupts:
0, 1, 2, 8, 9, 10, 11, 12, 13, 14, 15, 3, 4, 5, 6, 7
*/

struct interrupt_frame{
  uint16_t ip;
  uint16_t cs;
  uint16_t flags;
  uint16_t sp;
  uint16_t ss;
};

//void interrupt_handler(struct interrupt_frame *frame);
void prepare_interrupts();
bool handle_interrupt(void);
//__attribute__((interrupt))
void interrupt_handler(struct interrupt_frame *frame);
