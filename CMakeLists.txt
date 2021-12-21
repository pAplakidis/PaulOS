cmake_minimum_required(VERSION 3.10)
project(PaulOS C ASM)

# TODO:
#i686-elf-as boot.s -o boot.o
#i686-elf-gcc -c $(KERNEL_DIR)kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
#i686-elf-gcc -T linker.ld -o PaulOS.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

set(CMAKE_C_COMPILER i686-elf-gcc)
enable_language(ASM-ATT)
set(CMAKE_ASM_COMPILER i686-elf-as)
#set(CFLAGS "-std=gnu99 -ffreestanding -O2 -Wall -Wextra")

include_directories(src/kernel src/userland/libraries/libc)

file(GLOB_RECURSE C_SRCS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
message(STATUS "c files: ${C_SRCS}")
message(STATUS "c flags: ${CFLAGS}")
message(STATUS "asm compiler: ${CMAKE_ASM_COMPILER}")
message(STATUS "c compiler: ${CMAKE_C_COMPILER}")

#add_compile_options(${CFLAGS})
add_compile_options(-c -Wall -Wextra -O2 -ffreestanding -std=gnu99)  # TODO: use variable

# TODO: compile interrupts.c separately since it needs the following flags:
# $CC -mno-red-zone -mgeneral-regs-only -c .c -o .o

# TODO: compile gdt.s as well
add_library(boot.o src/boot.s)
add_library("${PROJECT_NAME}.o" ${C_SRCS})  # TODO: each file must produce it's own .o
#set_target_properties("${PROJECT_NAME}" PROPERTIES CFLAGS ${CFLAGS})

# TODO: link

