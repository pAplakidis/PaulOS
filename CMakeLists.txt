cmake_minimum_required(VERSION 3.10)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(PaulOS C ASM)

include_directories(src/ src/userland/libraries/libc)

enable_language(ASM)
set(CMAKE_ASM_COMPILER i686-elf-as)
set(CMAKE_C_COMPILER i686-elf-gcc)
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf")
set(CFLAGS "-O2 -g -ffreestanding -Wall -Wextra -nostdlib -std=gnu11")
set(CMAKE_C_FLAGS "${CFLAGS}")
set(CMAKE_ASM_FLAGS)

file(GLOB_RECURSE C_SRCS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
file(GLOB_RECURSE ASM_SRCS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.s")
file(GLOB_RECURSE kernel_C_SRCS "src/kernel/*.c")
file(GLOB_RECURSE kernel_ASM_SRCS "src/kernel/*.s")

message(STATUS "c files: ${C_SRCS}")
message(STATUS "kernel c files: ${kernel_C_SRCS}")
message(STATUS "kernel asm files: ${kernel_ASM_SRCS}")
message(STATUS "c flags: ${CFLAGS}")
message(STATUS "asm compiler: ${CMAKE_ASM_COMPILER}")
message(STATUS "c compiler: ${CMAKE_C_COMPILER}")

# TODO: compile gdt.s as well
#add_library(kernel.img STATIC ${kernel_ASM_SRCS} ${C_SRCS})

add_library(PaulOS.img STATIC
                       ${C_SRCS})

add_custom_command(TARGET PaulOS.img
                   POST_BUILD
                   COMMAND i686-elf-gcc -T ${CMAKE_CURRENT_LIST_DIR}/linker.ld -o PaulOS.bin -ffreestanding -O2 -nostdlib ${CMAKE_BINARY_DIR}/libPaulOS.img.a -lgcc)

