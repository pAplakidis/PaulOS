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
  tputs(uint_to_string((uint32_t)1234567890));
  tputs("\n");
  tputs(int_to_string((int32_t)-1234567890));
  tputs("\n");
  tputs(double_to_string((double)13.14));
  tputs("\n");
  tputs(double_to_string((double)-13.14));
  tputs("\n");

  // TODO: debug this
  //terminal_writestring(to_hstring((uint32_t)0x1234ABCDEF));
  //terminal_writestring("\n");

  // test kprintf (needs debugging)
  kprintf("Hello World!\n");
  kprintf("This is Mr Kernel\n");
  kprintf("Testing char %c\n", 'a');
  kprintf("Testing string %s\n", "random stuff");
  kprintf("Testing number %d\n", 10);
  kprintf("I am number %d, %c!\n", 1, 'A');
  char *temp_buf = "Testing serial!\n";
  serial_puts(temp_buf);

}

