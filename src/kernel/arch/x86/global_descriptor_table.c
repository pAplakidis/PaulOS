#include "global_descriptor_table.h"

void encode_GDT_entry(uint8_t* target, struct GDT src){
  // check if the limit can be encoded
  if((src.limit > 65536) && ((src.limit & 0xfff) != 0xfff)){
    // TODO: implement messages such as kerror
  }

  if(src.limit > 65536){
    // adjust granularity if required
    src.limit >>= 12;
    target[6] = 0xc0;
  }
  else{
    target[6] = 0x40;
  }

  // encode the limit
  target[0] = src.limit & 0xff;
  target[1] = (src.limit >> 8) & 0xff;
  target[6] = (src.limit >> 16) & 0xf;

  // encode the base
  target[2] = src.base & 0xff;
  target[3] = (src.base >> 8) & 0xff;
  target[4] = (src.base >> 16) & 0xff;
  target[7] = (src.base >> 24) & 0xff;

  // encode the type
  target[5] = src.type;
}

// TODO: some assembly code is needed for telling the CPU where the table stands and reloading segment registers

void create_descriptor(uint32_t base, uint32_t limit, uint16_t flag){
  uint64_t descriptor;

  // create the high 32 bit segment
  descriptor = limit & 0x000f0000;  // set limit bits 19:16
  descriptor |= (flag << 8) & 0x00f0ff00;  // set type, p, dpl, s, g, d/b, l and avl fields
  descriptor |= (base >> 16) & 0x000000ff;  // set base bits 23:16
  descriptor |= base & 0xff000000;  // set base bits 31:24
}
