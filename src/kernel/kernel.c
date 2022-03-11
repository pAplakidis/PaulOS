#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/tty/tty.h>
#include "kernel/kstdio.h"
#include <kernel/arch/x86/global_descriptor_table.h>
#include <kernel/arch/x86/interrupts.h>
#include <kernel/arch/x86/multiboot.h>

// Check if the compiler thinks you are targeting the wrong operating system
#if defined(__linux__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif 

struct GDT_desc gdt_desc;

// TODO: change GDT and IDT from 64bit to 32bit!!!

// MAIN
void kernel_main(multiboot_info_t* mbd, uint32_t magic){
  // INIT KERNEL
  // initialize terminal interface
  terminal_initialize();

  // ---------------------------------------------------------

  //init_GDT();
  gdt_desc.size = sizeof(GDT) -1;
  gdt_desc.offset = (uint32_t)&default_GDT;
  kprintf("GDT size: %d\n", gdt_desc.size);
  kprintf("GDT offset: 0x%x\n", gdt_desc.offset);
  //load_GDT(&gdt_desc);  // TODO: this crashes
  kprintf("[Kernel]: GDT initialized\n");

  // ---------------------------------------------------------

  // get memory map via GRUB
  kprintf("magic: %d\n", magic);
  // make sure the magic number matches for memory mapping
  if(magic != MULTIBOOT_BOOTLOADER_MAGIC){
    // TODO: panic
    kprintf("[Kernel Panic] Invalid magic number\n");
  }

  // check bit 6 to see if we have a valid memory map
  if(!mbd->flags >> 6 & 0x1){
    kprintf("[Kernel Panic]: Invalid memory map given by GRUB\n");
  }

  // loop through the memory map and display the values
  for (int i=0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)){
    multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*)(mbd->mmap_addr + i);
    kprintf("Start Addr: 0x%x | ", mmmt->addr);
    kprintf("Length : 0x%x | ", mmmt->len);
    kprintf("Size: 0x%x | ", mmmt->size);
    kprintf("Type: %d\n", mmmt->type);

    if(mmmt->type = MULTIBOOT_MEMORY_AVAILABLE){
      // TODO
      /*
      Do something with this memory block
      WARNING: some of memory shown as available is actually
      actively being used by the kernel.
      */
    }
  }

  // ---------------------------------------------------------

  // test printing integers on tty
  tputs(uint_to_string((uint32_t)1234567890));
  tputs("\n");
  tputs(int_to_string((int32_t)-1234567890));
  tputs("\n");
  tputs(double_to_string((double)13.14));
  tputs("\n");
  tputs(double_to_string((double)-13.14));
  tputs("\n");
  tputs(hex_to_string((uint32_t)0x1234abcd));
  tputs("\n");

  // test kprintf
  /*
  kprintf("Hello World!\n");
  kprintf("This is Mr Kernel\n");
  kprintf("Testing char %c\n", 'a');
  kprintf("Testing string %s\n", "random stuff");
  kprintf("Testing decimal %d\n", 10);
  kprintf("Testing hex 0x%x\n", 0x1234cdef);
  kprintf("Testing float %f\n", 3.14);
  kprintf("Testing negative float %f\n", -3.14);
  kprintf("I am number %d, %c!\n", 1, 'A');
  */
}

