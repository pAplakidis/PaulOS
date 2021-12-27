#include "kstdio.h"

const char* int_to_string(uint32_t val){
  char buf[BUF_SIZE];

  uint8_t size = 0;
  uint32_t size_test = val;
  while(size_test / 10 > 0){
    size_test /= 10;
    size++;
  }

  uint8_t idx = 0;
  while(val / 10 > 0){
    uint8_t remainder = val % 10;
    val /= 10;
    buf[size-idx] = remainder + '0';
    idx++;
  }
  
  uint8_t remainder = val % 10;
  buf[size-idx] = remainder + '0';
  buf[size-idx+1] = 0;
  return buf;
}

// TODO: check out [https://stackoverflow.com/questions/54352400/implementation-of-printf-function]
// and [https://github.com/stevej/osdev/blob/master/kernel/misc/kprintf.c]
void kprintf(char* buf, const char* fmt, ...){
  va_list ap;
  va_start(ap, fmt);

  uint8_t *ptr;

  // TODO: instead of printing on TTY, we can just make a proper buffer and then output it wherever we want
  // TODO: this is temp, need to make more generic (use lexical-analysis/NFA/DFA maybe?)
  for(ptr = fmt; *ptr != '\0'; ptr++){
    if(*ptr == "%"){
      ptr++;
      switch(*ptr){
        case 's':
          terminal_writestring(va_arg(ap, uint8_t *));
          break;
        case 'd':
          break;
        default:
          // TODO: handle error
          break;
      }
    }
    else{
      // TODO: the tty stuff are temp, need to output to a serial port for debugcon
      terminal_putchar(*ptr);
      ptr++;
    }
  }

  va_end(ap);
}
