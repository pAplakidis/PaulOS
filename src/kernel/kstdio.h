#pragma once
#define BUF_SIZE        64

#include <stdarg.h>
#include <stdint.h>

#include "kernel/tty/tty.h"
#include "kernel/arch/x86/io.h"

// TODO: these functions are wrong!!
const char* uint_to_string(uint32_t val);
const char* int_to_string(int32_t val);
const char* to_hstring(uint32_t val);
const char* to_hstring_16(uint16_t val);
const char* to_hstring_8(uint8_t val);
// TODO: implement hstring for 8 an 16 bits as well [https://www.youtube.com/watch?v=E42JEc-t3ZA&list=PLxN4E629pPnJxCQCLy7E0SQY_zuumOVyZ&index=4&t=2s&ab_channel=Poncho]
const char* double_d_to_string(double val, uint8_t decimal_places);
const char* double_to_string(double val);
void print_dec(char* bug, uint32_t val);

void serial_putch(char c);
void kprintf(const char* fmt, ...);
