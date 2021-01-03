#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Check if the compiler thinks you are targeting the wrong operating system
#if defined(__linux__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif 

// Hardware text mode color constants
enum vga_color{
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg){
  return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color){
  return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str){
  size_t len = 0;
  while(str[len])
    len++;
  return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void){
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = (uint16_t*) 0xB8000;
  
  for(size_t y = 0; y < VGA_HEIGHT; y++){
    for(size_t x = 0; x<VGA_WIDTH; x++){
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_setcolor(uint8_t color){
  terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y){
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll(){
  for(size_t y = 0; y < VGA_HEIGHT; y++){
    for(size_t x = 0; x<VGA_WIDTH; x++){
      const size_t index1 = y * VGA_WIDTH + x;
      const size_t index2 = (y+1) * VGA_WIDTH + x;
      terminal_buffer[index1] = terminal_buffer[index2];
    }
  }
}

void terminal_putchar(char c){
  // Handle newline
  if(c == '\n'){
    terminal_row++;
    terminal_column = 0;
  }
  else{

    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    // If we reach the end of a line, continue at the start of the next
    if(++terminal_column == VGA_WIDTH){
      terminal_column = 0;
      terminal_row++;
      /*
      if(++terminal_row == VGA_HEIGHT)
        terminal_row = 0;
      */
    }
  }

  // Scroll temrinal when we reach bottom
  if(terminal_row >= VGA_HEIGHT){
    terminal_column = 0;
    terminal_row--;
    terminal_scroll();
    terminal_putentryat(c, terminal_color, terminal_column, VGA_HEIGHT-1);
  }
}

void terminal_write(const char* data, size_t size){
  for(size_t i = 0; i < size; i++)
    terminal_putchar(data[i]);
}

void terminal_writestring(const char* data){
  terminal_write(data, strlen(data));
}

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

