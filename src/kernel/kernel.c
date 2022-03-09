#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "kernel/tty/tty.h"
#include "kernel/kstdio.h"
#include "kernel/arch/x86/global_descriptor_table.h"
#include "kernel/arch/x86/interrupts.h"

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
  //load_GDT(&gdt_desc);
}

// MAIN
void kernel_main(void){
  kinit();

  // test printing integers
  terminal_writestring(uint_to_string((uint32_t)1234567890));
  terminal_writestring("\n");
  terminal_writestring(int_to_string((int32_t)-1234567890));
  terminal_writestring("\n");
  /*
  // TODO: these crash the system
  terminal_writestring(double_to_string((double)13.14));
  terminal_writestring("\n");
  terminal_writestring(double_to_string((double)-13.14));
  terminal_writestring("\n");
  */
  terminal_writestring(to_hstring((uint32_t)0x1234));
  terminal_writestring("\n");

  // test kprintf
  kprintf("Hello World!\n");
  kprintf("I am number %d!\n", 1);  // This is incorrect!

}

