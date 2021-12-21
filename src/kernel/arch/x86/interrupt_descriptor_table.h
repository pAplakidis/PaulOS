#pragma once
#include <stdint.h>

#define IDT_TA_InterruptGate  0b10001110
#define IDT_TA_CallGate       0b10001100
#define IDT_TA_TrapGate       0b10001111

// IDTR
struct IDT_desc{
  uint16_t limit;
  uint64_t offset;
}__attribute__((packed));

typedef struct IDT_entry{
  uint16_t offset0;  // offset bits 0:15
  uint16_t selector; // a code segment selector in GDT or LDT
  uint8_t ist;       // bits 0:2 interrupt stack table offset, rest is 0
  uint8_t type_attr; // gate type, dpl and p fields
  uint16_t offset1;  // offset bits 16:31
  uint32_t offset2;  // offset bits 32:63
  uint32_t zero;      // unused/reserved, set to 0
}__attribute__((packed)) IDT_entry;

// for IDTR
void idtr_set_offset(uint64_t offset, struct IDT_entry* idt_entry);
uint64_t idtr_get_offset(struct IDT_entry idt_entry);
