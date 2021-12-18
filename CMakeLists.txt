cmake_minimum_required(VERSION 3.10)
project(PaulOS)

# TODO:
#i686-elf-as boot.s -o boot.o
#i686-elf-gcc -c $(KERNEL_DIR)kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
#i686-elf-gcc -T linker.ld -o PaulOS.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

set(CMAKE_C_COMPILER i686-elf-gcc)
set(CFLAGS "-std=gnu99 -ffreestanding -O2 -Wall -Wextra")

include_directories(src/)

file(GLOB_RECURSE C_SRCS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
#message(STATUS "c files: ${C_SRCS}")

enable_language(ASM-ATT)

add_executable(boot src/boot.s)
add_executable("${PROJECT_NAME}" ${C_SRCS})
set_target_properties("${PROJECT_NAME}" PROPERTIES CFLAGS ${CFLAGS})

