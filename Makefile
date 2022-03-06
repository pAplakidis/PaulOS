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



#compile: $(OBJS)
	#i686-elf-as $(SRC_DIR)boot.s -o $(BUILD_DIR)boot.o
	#i686-elf-gcc -c $(SRCS) -o $(BUILD_DIR)kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	#i686-elf-gcc -T linker.ld -o $(BUILD_DIR)PaulOS.bin -ffreestanding -O2 -nostdlib $(BUILD_DIR)boot.o $(BUILD_DIR)kernel.o -lgcc
	#i686-elf-gcc -T linker.ld -o $(BUILD_DIR)PaulOS.bin -ffreestanding -O2 -nostdlib $^ -lgcc

#$(BUILD_DIR)%.o: $(SRC_DIR)%.c
#	$(CC) -I$(SRC_DIR) -c $< -o $@ $(CFLAGS)

all: PaulOS.bin

PaulOS.bin: $(OBJ) boot ./linker.ld
	$(CC) -T ./linker.ld -o $@ $(LDFLAGS) $(OBJ) -lgcc
	echo "[+] Linked objects"

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	echo "[+] C sources built"

boot: $(SRC_DIR)boot.s
	i686-elf-as $< -o boot.o
	echo "[+] Boot built"

