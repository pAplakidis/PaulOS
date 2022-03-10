#pragma once
#define BUF_SIZE  128

#include <stdarg.h>
#include <stdint.h>

#include "kernel/tty/tty.h"
#include "kernel/arch/x86/io.h"

// TODO: these functions are wrong!!
const char* uint_to_string(uint32_t val);
const char* int_to_string(int32_t val);
const char* hex_to_string(uint32_t val);
const char* double_d_to_string(double val, uint8_t decimal_places);
const char* double_to_string(double val);

void serial_putch(char c);
void kprintf(const char* fmt, ...);
