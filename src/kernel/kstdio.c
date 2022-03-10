#include "kstdio.h"

// TODO: create separate buffers above each to_string function!!!
char buf[BUF_SIZE];
char hbuf[BUF_SIZE];
char serial_stdout[BUF_SIZE];

void reset_buf(){
  for(int i=0; i<BUF_SIZE; i++){
    buf[i] = 0x0;
  }
}

void reset_hbuf(){
  for(int i=0; i<BUF_SIZE; i++){
    hbuf[i] = 0x0;
  }
}

void reset_sstdout(){
  for(int i=0; i<BUF_SIZE; i++){
    serial_stdout[i] = 0x0;
  }
}

const char* uint_to_string(uint32_t val){
  reset_buf();

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
  buf[size+1] = 0;
  return buf;
}

const char* int_to_string(int32_t val){
  reset_buf();

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
  buf[is_negative+size+1] = 0;
  return buf;
}

// TODO: BUG HERE, prints crap
const char* to_hstring(uint32_t val){
  reset_hbuf();

  uint32_t* val_ptr = &val;
  uint8_t* ptr;
  uint8_t tmp;
  uint8_t size = 8 * 2 - 1;

  for(uint8_t i=0; i<size; i++){
    ptr = ((uint8_t*)val_ptr + i);
    tmp = (*ptr & 0xf0) >> 4;
    hbuf[size - (i*2 + 1)] = tmp + (tmp > 9 ? 'A' : '0');
    tmp = (*ptr & 0x0f);
    hbuf[size - (i*2)] = tmp + (tmp > 9 ? 'A' : '0');
  }

  hbuf[size + 1] = 0;
  return hbuf;
}

const char* to_hstring_16(uint16_t val){
  reset_buf();

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

const char* to_hstring_8(uint8_t val){
  reset_buf();

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
  reset_hbuf();

  char* int_ptr = (char*)int_to_string((int32_t)val);
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

void serial_putch(char c){
  // output to QEMU debugcon
  out8(0xe9, (uint8_t)c);
}

// TODO: bug here!!!! (keeps printing until it crashes)
void serial_puts(const char* buf){
  char *buf_ptr = buf;
  while(buf_ptr != 0){
    serial_putch(*buf_ptr);
    //terminal_putchar(*buf_ptr); // NOTE: temp for debugging
    buf_ptr++;
  }
}

// TODO: check out [https://stackoverflow.com/questions/54352400/implementation-of-printf-function]
// and [https://github.com/stevej/osdev/blob/master/kernel/misc/kprintf.c]

// This behaves like sprintf(), buf can be used to print either on tty or on a serial port
void kprintf(const char* fmt, ...){
  reset_sstdout();

  va_list ap;
  va_start(ap, fmt);

  uint8_t *ptr;
  char* buf_ptr = serial_stdout;
  char* src_ptr;
  char* temp_buf;

  for(ptr = fmt; *ptr != '\0'; ptr++){
    if(*ptr == '%'){
      ptr++;
      switch(*ptr){
        case 'c':
          *buf_ptr++ = (char)va_arg(ap, int);
          break;
        // TODO: these two need debugging
        case 's':
          src_ptr = (char*)va_arg(ap, char *);
          while(*src_ptr != 0){
            *buf_ptr++ = *src_ptr++;
          }
          break;
        case 'd':
          temp_buf = (char*)int_to_string((int32_t)va_arg(ap, int32_t *));
          src_ptr = temp_buf;
          while(*src_ptr != 0){
            *buf_ptr++ = *src_ptr++;
          }
          break;
        case 'x':
          // TODO: handle hex numbers here
          break;
        default:
          break;
      }
    }
    else{
      *buf_ptr++ = *ptr;
    }
  }

  va_end(ap);
  tputs(serial_stdout);
  //serial_puts(serial_stdout); // TODO: BUG HERE (seems to crash)
}
