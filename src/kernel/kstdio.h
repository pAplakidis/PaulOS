#pragma once
#define BUF_SIZE  16
#define UINT32_MAX

#include <stdarg.h>
#include <stdint.h>

#include "kernel/tty/tty.h"

char* int_to_string(int number);
void print_dec(char* bug, uint32_t val);
void kprintf(char* buf, const char* fmt, ...);
