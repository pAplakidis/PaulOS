#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/tty/tty.h>
#include "kernel/kstdio.h"
#include <kernel/arch/x86/global_descriptor_table.h>
#include <kernel/arch/x86/interrupts.h>

// Check if the compiler thinks you are targeting the wrong operating system
/*
#if defined(__linux__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif 
*/

struct GDT_desc gdt_desc;

// TODO: change GDT and IDT from 64bit to 32bit!!!

void kinit(){
  // initialize terminal interface
  terminal_initialize();

  //init_GDT();
  gdt_desc.size = sizeof(GDT) -1;
  gdt_desc.offset = (uint32_t)&default_GDT;
  kprintf("GDT size: %d\n", gdt_desc.size);
  kprintf("GDT offset: 0x%x\n", gdt_desc.offset);
  //load_GDT(&gdt_desc);  // TODO: this crashes
}

// MAIN
void kernel_main(void){
  kinit();

  // test printing integers on tty
  tputs(uint_to_string((uint32_t)1234567890));
  tputs("\n");
  tputs(int_to_string((int32_t)-1234567890));
  tputs("\n");
  tputs(double_to_string((double)13.14));
  tputs("\n");
  tputs(double_to_string((double)-13.14));
  tputs("\n");
  tputs(hex_to_string((uint32_t)0x1234abcd));
  tputs("\n");

  // test kprintf
  kprintf("Hello World!\n");
  kprintf("This is Mr Kernel\n");
  kprintf("Testing char %c\n", 'a');
  kprintf("Testing string %s\n", "random stuff");
  kprintf("Testing decimal %d\n", 10);
  kprintf("Testing hex 0x%x\n", 0x1234cdef);
  kprintf("Testing float %f\n", 3.14);
  kprintf("Testing negative float %f\n", -3.14);
  kprintf("I am number %d, %c!\n", 1, 'A');
}

