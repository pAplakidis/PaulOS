SRC_DIR = src/
KERNEL_DIR = src/kernel/
BUILD_DIR = build/
LIBC_DIR = src/userland/libraries/libc

INC=-I$(SRC_DIR) -I$(LIBC_DIR)

C_SRCS := $(shell find $(SOURCEDIR) -type f -name '*.c')
OBJ := $(C_SRCS:.c=.o)
KS_SRCS := $(shell find $(KERNEL_DIR) -name '*.s')
#OBJS := $(patsubst $(C_SRCS), %.o, $(C_SRCS))

CC := i686-elf-gcc
AS := i686-elf-as
CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS := -ffreestanding -O2 -nostdlib

$(info $$C_SRCS is [${C_SRCS}])

all: PaulOS.bin

PaulOS.bin: $(OBJ) boot.o ./linker.ld
	$(CC) -T ./linker.ld -o $@ $(LDFLAGS) boot.o $(OBJ) -lgcc
	echo "[+] Linked objects"

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	echo "[+] C sources built"

boot.o: $(SRC_DIR)boot.s
	$(AS) $< -o boot.o
	echo "[+] Boot built"

