cmake_minimum_required(VERSION 3.10)
project(PaulOS C ASM)

# TODO: check out [https://github.com/phaser/phOS/blob/master/CMakeLists.txt]
# as well as [https://github.com/mallardtheduck/osdev/blob/master/CMakeLists.txt]

enable_language(ASM)
set(CMAKE_ASM_COMPILER i686-elf-as)
set(CMAKE_C_COMPILER i686-elf-gcc)
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf")
set(CFLAGS "-Wall -Wextra -O2 -ffreestanding -std=gnu99")
set(CMAKE_C_FLAGS "${CFLAGS}")
set(CMAKE_ASM_FLAGS)

include_directories(src/ src/userland/libraries/libc)

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


add_library(PaulOS.img STATIC src/boot.s ${C_SRCS})

add_custom_command(TARGET PaulOS.img POST_BUILD
                   COMMAND i686-elf-gcc -T${CMAKE_CURRENT_LIST_DIR}/linker.ld -o PaulOS.bin -ffreestanding -O2 -nostdlib ${CMAKE_BINARY_DIR}/libPaulOS.img.a -lgcc)

#[[
SET (CMAKE_C_FLAGS "-ffreestanding -nostdlib -Wall -Wextra -O2")
SET (CMAKE_EXE_LINKER_FLAGS "-m elf_i386 -T${CMAKE_CURRENT_LIST_DIR}/link.ld")
SET (CMAKE_ASM_NASM_OBJECT_FORMAT "elf")

ENABLE_LANGUAGE (ASM_NASM)

file(GLOB_RECURSE C_SRCS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
include_directories(src/ src/userland/libraries/libc)

FILE (GLOB_RECURSE kernel_C_SOURCES "kernel/*.c")
FILE (GLOB_RECURSE kernel_CPP_SOURCES "kernel/*.cpp")
FILE (GLOB_RECURSE kernel_ASM_SOURCES "arch/x86/asm/*.nasm")
FILE (GLOB_RECURSE kernel_ARCH_C_SOURCES "arch/x86/*.c")
FILE (GLOB_RECURSE kernel_ARCH_CPP_SOURCES "arch/x86/*cpp")

ADD_LIBRARY (kernel.img STATIC ${C_SRCS} src/boot.asm)

#ADD_CUSTOM_COMMAND (TARGET kernel.img
#	POST_BUILD
#  COMMAND "/usr/bin/ld -m elf_i386 -T${CMAKE_CURRENT_LIST_DIR}/link.ld -o PaulOS.bin ${CMAKE_BINARY_DIR}/libkernel.img.a")
]]

