#pragma once
#define BUF_SIZE  16

#include <stdarg.h>
#include <stdint.h>

#include "kernel/tty/tty.h"

char* int_to_string(int number);
void kprintf(char* buf, const char* fmt);
