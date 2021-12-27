#pragma once
#define BUF_SIZE        64

#include <stdarg.h>
#include <stdint.h>

#include "kernel/tty/tty.h"

const char* uint_to_string(uint32_t val);
const char* int_to_string(int32_t val);
const char* to_hstring(uint32_t val);
const char* double_d_to_string(double val, uint8_t decimal_places);
const char* double_to_string(double val);
void print_dec(char* bug, uint32_t val);
void kprintf(char* buf, const char* fmt, ...);
