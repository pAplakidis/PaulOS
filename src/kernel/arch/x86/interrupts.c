#include "interrupts.h"

/*
__attribute__ ((interrupt))
void interrupt_handler(struct interrupt_frame *frame){
  __asm__("pushad");
  __asm__("popad; leavue; iret");
}
*/

struct IDT_desc idt_desc; // IDTR

void prepare_interrupts(){
  idt_desc.limit = 0x0fff;
  idt_desc.offset = (uint64_t)0;  // TODO: to make a global allocator and request_page()

  IDT_entry* int_page_fault = (IDT_entry*)(idt_desc.offset + 0xe * sizeof(IDT_entry));
  idtr_set_offset((uint64_t)page_fault_handler, int_page_fault);
  int_page_fault->type_attr = IDT_TA_InterruptGate;
  int_page_fault->selector = 0x08;

  asm("lidt %0" : : "m" (idt_desc));
}

__attribute__((interrupt))
void page_fault_handler(struct interrupt_frame* frame){
  // TODO: print "Page fault detected" for debugging
  while(1);
}
