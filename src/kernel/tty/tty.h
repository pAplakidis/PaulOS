#pragma once
#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

#include "arch/x86/vga.h"
#include "string.h"

void terminal_initialize(void);
void temrinal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_clear();

#endif

