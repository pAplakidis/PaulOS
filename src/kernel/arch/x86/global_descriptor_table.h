#pragma once
//#include <stdio.h>
#include <stdint.h>

// each define corresponds to a specific flag in the descriptor (check intel docs)
#define SEG_DESCTYPE(x)   ((x) << 0x04) // descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x)       ((x) << 0x07) // present
#define SEG_SAVL(x)       ((x) << 0x0C) // available for system use
#define SEG_LONG(x)       ((x) << 0x0D) // long mode
#define SEG_SIZE(x)       ((x) << 0x0E) // size (0 for 16bit, 1 for 32)
#define SEG_GRAN(x)       ((x) << 0x0F) // granularity (0 for 1B-1MB, 1 for 4KB-4GB)
#define SEG_PRIV(x)       (((x) & 0x03) << 0x03) // set privilege level (0-3)

#define SEG_DATA_RD       0x00  // read-only
#define SEG_DATA_RDA      0x01  // read-only, accessed
#define SEG_DATA_RDWR     0x02  // read/write
#define SEG_DATA_RDWRA    0x03  // read/write, accessed
#define SEG_DATA_RDEXPD   0x04  // read-only, expand-down
#define SEG_DATA_RDEXPDA  0x05  // read-only, expand-down, accessed
#define SEG_DATA_RDWREXPD 0x06  // read/write, expand-down
#define SEG_DATA_RDWREXPDA 0x07  //read/write, expand-down, accessed
#define SEG_CODE_EX       0x08  // execute-only
#define SEG_CODE_EXA      0x09  // execute-only, accessed
#define SEG_CODE_EXRD     0x0A  // execute/read
#define SEG_CODE_EXRDA    0x0B  // execute/read, accessed
#define SEG_CODE_EXC      0x0C  // execute-only, conforming
#define SEG_CODE_EXCA     0x0D  // execute-only, conforming, accessed
#define SEG_CODE_EXRDC    0x0E  // execute/read, conforming
#define SEG_CODE_EXRDCA   0x0F  // execute/read, conforming, accessed

#define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_CODE_EXRD
 
#define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_DATA_RDWR
 
#define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_CODE_EXRD
 
#define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_DATA_RDWR

// GDTR
struct GDT_desc{
  uint16_t size;
  uint64_t offset;
}__attribute__((packed));

// Global Offset Table Descriptor
typedef struct GDT_entry{
  uint16_t limit0;
  uint16_t base0;
  uint8_t base1;
  uint8_t accessbyte;
  uint8_t limit1_flags;
  uint8_t base2;
}__attribute__((packed)) GDT_entry;

typedef struct GDT{
  GDT_entry null; // 0x00
  GDT_entry kernel_code;  // 0x08
  GDT_entry kernel_data;  // 0x10
  GDT_entry user_null;
  GDT_entry user_code;
  GDT_entry user_data;
}__attribute__((packed)) __attribute__((aligned(0x1000))) GDT;

//void encode_GDT_entry(uint8_t* target, struct GDT_entry src);
uint64_t create_descriptor(uint32_t base, uint32_t limit, uint16_t flag);

extern struct GDT default_GDT;
//extern void load_GDT(struct GDT_desc* gdt_desc);
