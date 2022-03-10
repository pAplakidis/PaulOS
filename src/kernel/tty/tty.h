#pragma once
#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#define BUF_SIZE  32

#include <stddef.h>

#include "kernel/arch/x86/vga.h"
#include "kernel/string.h"

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void tputs(const char* data);
void terminal_writedec(uint32_t val);
void terminal_clear();

#endif

