.globl load_GDT
load_GDT:
  lgdt (%edi)
  mov 0x10, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  mov %ax, %ss
  pop %edi
  mov 0x08, %eax
  push %eax
  push %edi
  #retfq
  ret

