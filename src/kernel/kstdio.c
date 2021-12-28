#include "kstdio.h"

const char* uint_to_string(uint32_t val){
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

const char* int_to_string(int32_t val){
  char buf[BUF_SIZE];

  uint8_t is_negative = 0;
  if(val < 0){
    is_negative = 1;
    val *= -1;
    buf[0] = '-';
  }

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
    buf[is_negative+size-idx] = remainder + '0';
    idx++;
  }
  
  uint8_t remainder = val % 10;
  buf[is_negative+size-idx] = remainder + '0';
  buf[is_negative+size-idx+1] = 0;
  return buf;
}

const char* to_hstring(uint32_t val){
  char buf[BUF_SIZE];
  uint32_t* val_ptr = &val;
  uint8_t* ptr;
  uint8_t tmp;
  uint8_t size = 8 * 2 - 1;

  for(uint8_t i=0; i<size; i++){
    ptr = ((uint8_t*)val_ptr + i);
    tmp = (*ptr & 0xf0) >> 4;
    buf[size - (i*2 + 1)] = tmp + (tmp > 9 ? 'A' : '0');
    tmp = (*ptr & 0x0f);
    buf[size - (i*2)] = tmp + (tmp > 9 ? 'A' : '0');
  }

  buf[size + 1] = 0;
  return buf;
}

const char* double_d_to_string(double val, uint8_t decimal_places){
  char* buf[BUF_SIZE];
  char* int_ptr = (char*)to_string((int64_t)val);
  char*double_ptr = buf;

  if(decimal_places > 20)
    decimal_places = 20;

  if(val < 0){
    val *= -1;
  }

  // copy the decimal part into the buffer
  while(*int_ptr != 0){
    *double_ptr = *int_ptr;
    int_ptr++;
    double_ptr++;
  }

  // add point
  *double_ptr = '.';
  double_ptr++;

  // get the number after the decimal point
  double new_val = val - (int32_t)val;
  for(uint8_t i=0; i<decimal_places; i++){
    new_val *= 10;
    *double_ptr = (int32_t)new_val + '0';
    new_val -= (int32_t)new_val;
    double_ptr++;
  }

  *double_ptr = 0;
  return buf;
}

const char* double_to_string(double val){
  return double_d_to_string(val, 2);
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
