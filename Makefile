SRC_DIR = src/
KERNEL_DIR = src/kernel/
BUILD_DIR = build/
LIBC_DIR = src/userland/libraries/libc

INC=-I$(SRC_DIR) -I$(LIBC_DIR)

C_SRCS := $(shell find $(SRC_DIR) -type f -name '*.c')
AS_SRCS := $(shell find $(SRC_DIR) -type f -name '*.S')
OBJ := $(C_SRCS:.c=.o)
OBJ += $(AS_SRCS:.s=.o)

CC := i686-elf-gcc
AS := i686-elf-as
CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS := -ffreestanding -O2 -nostdlib

$(info $$C_SRCS is [${C_SRCS}])
$(info $$AS_SRCS is [${AS_SRCS}])

all: PaulOS.bin

PaulOS.bin: $(OBJ) ./linker.ld
	$(CC) -T ./linker.ld -o $@ $(LDFLAGS) $(OBJ) -lgcc
	echo "[+] Linked objects"

.c.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	echo "[+] C sources built"
	
.S.o: %.S
	$(AS) $< -o $@
	echo "[+] AS sources built"

#boot.o: $(SRC_DIR)boot.S
#	$(AS) $< -o boot.o
#	echo "[+] Boot built"

