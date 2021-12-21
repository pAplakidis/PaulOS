#include "interrupt_descriptor_table.h"

// IDTR functions
void idtr_set_offset(uint64_t offset, struct IDT_entry* idt_entry){
  idt_entry->offset0 = (uint16_t)(offset & 0x000000000000ffff);
  idt_entry->offset1 = (uint16_t)((offset & 0x00000000ffff0000) >> 16);
  idt_entry->offset2 = (uint32_t)((offset & 0xffffffff00000000) >> 32);
}

uint64_t idtr_get_offset(struct IDT_entry idt_entry){
  uint64_t offset = 0;
  offset |= (uint64_t)idt_entry.offset0;
  offset |= (uint64_t)idt_entry.offset1 << 16;
  offset |= (uint64_t)idt_entry.offset2 << 32;

  return offset;
}
