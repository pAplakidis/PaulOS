#pragma once

#include <stdint.h>

inline void out8(uint16_t port, uint8_t val){
  asm volatile("outb %0, %1" :: "a"(val), "Nd"(port));
}

inline void out16(uint16_t port, uint16_t val){
  asm volatile("outw %0, %1" :: "a"(val), "Nd"(port));
}

inline void out32(uint16_t port, uint32_t val){
  asm volatile("outl %0, %1" :: "a"(val), "Nd"(port));
}
