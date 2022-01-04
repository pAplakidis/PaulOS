all: compile

SRC_DIR = src/
KERNEL_DIR = src/kernel/
SRCS := $(shell find $(SOURCEDIR) -name '*.c')

$(info $$SRCS is [${SRCS}])

compile:
	i686-elf-as $(SRC_DIR)boot.s -o boot.o
	i686-elf-gcc -c $(SRCS) -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o PaulOS.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

clean:
	rm boot.o
	rm kernel.o
	rm PaulOS.bin
	rm -rf isodir


