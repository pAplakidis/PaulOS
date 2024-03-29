#include "tty.h"

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
  for(size_t i = 0; i < size; i++){
    terminal_putchar(data[i]);
    /*
    // test different colors
    if(i <= 14)
      terminal_color = vga_entry_color(i+1, VGA_COLOR_BLACK);
    */
    }
}

void tputs(const char* data){
  terminal_write(data, kstrlen(data));
}

// convert integer to string and print it
void terminal_writedec(uint32_t val){
  char buf[BUF_SIZE];

  uint32_t n_width = 1;
  uint32_t i = 9;
  while(val > i && i < UINT32_MAX){
    n_width += 1;
    i *= 10;
    i += 9;
  }

  int32_t printed = 0;
  int32_t* ptr; // TODO: ptr might be cursor pointer, handle it better!
  while(n_width + printed < VGA_WIDTH){
    buf[*ptr] = '0';
    (*ptr)++;
    printed++;
  }

  i = n_width;
  while(i > 0){
    uint32_t n = val / 10;
    int32_t r = val & 10;
    buf[*ptr + i - 1] = r + '0';
    i--;
    val = n;
  }
  *ptr += n_width;

  tputs((const char*)buf);

  // TODO: maybe use these for now (or writestring(buf))
  /*
  terminal_putentryat('', terminal_color, terminal_column, terminal_row);
  // If we reach the end of a line, continue at the start of the next
  if(++terminal_column == VGA_WIDTH){
    terminal_column = 0;
    terminal_row++;
  }
  */
}

void terminal_clear(){
  for(size_t y = 0; y < VGA_HEIGHT; y++){
    for(size_t x = 0; x<VGA_WIDTH; x++){
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}
