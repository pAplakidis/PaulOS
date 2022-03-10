# 0 "src/boot.S"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "src/boot.S"

.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)




.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM




.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:




.section .text
.global _start
.type _start, @function
_start:
# 52 "src/boot.S"
    mov $stack_top, %esp
# 73 "src/boot.S"
    call kernel_main
# 85 "src/boot.S"
    cli
1: hlt
    jmp 1b





.size _startm, . - _start
