#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "tty/tty.h"

// Check if the compiler thinks you are targeting the wrong operating system
#if defined(__linux__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif 

// MAIN
void kernel_main(void){
  // initialize terminal interface
  terminal_initialize();

  // Test scrolling
  terminal_writestring("1) Hello, kernel World!\n2) This is Paul's Operating System\n");
  terminal_writestring("3) Hello, kernel World!\n4) This is Paul's Operating System\n");
  terminal_writestring("5) Hello, kernel World!\n6) This is Paul's Operating System\n");
  terminal_writestring("7) Hello, kernel World!\n8) This is Paul's Operating System\n");
  terminal_writestring("9) Hello, kernel World!\n10) This is Paul's Operating System\n");
  terminal_writestring("11) Trying to\n12) Reach the bottom\n");
  terminal_writestring("13) Trying to\n14) Reach the bottom\n");
  terminal_writestring("14) Trying to\n16) Reach the bottom\n");
  terminal_writestring("17) Trying to\n18) Reach the bottom\n");
  terminal_writestring("19) Trying to\n20) Reach the bottom\n");
  terminal_writestring("21) Trying to\n22) Reach the bottom\n");
  terminal_writestring("Trying to..\nReached it\n");
  terminal_writestring("Let's go further down\n");
  // Test horizontal limit combined with scrolling
  terminal_writestring("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAATop should be at 4)\n");
  // Test if we can actually write in line 25 (botton of the terminal)
  terminal_writestring("Hello from the bottom!");
}

