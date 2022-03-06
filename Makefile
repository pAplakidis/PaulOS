SRC_DIR = src/
KERNEL_DIR = src/kernel/
BUILD_DIR = build/

C_SRCS := $(shell find $(SOURCEDIR) -name '*.c')
KS_SRCS := $(shell find $(KERNEL_DIR) -name '*.s')
OBJS := $(patsubst $(C_SRCS), %.o, $(C_SRCS))

CC := i686-elf-gcc
AS := i686-elf-as
CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra

$(info $$C_SRCS is [${C_SRCS}])

all: kernel

#compile: $(OBJS)
	#i686-elf-as $(SRC_DIR)boot.s -o $(BUILD_DIR)boot.o
	#i686-elf-gcc -c $(SRCS) -o $(BUILD_DIR)kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	#i686-elf-gcc -T linker.ld -o $(BUILD_DIR)PaulOS.bin -ffreestanding -O2 -nostdlib $(BUILD_DIR)boot.o $(BUILD_DIR)kernel.o -lgcc
	#i686-elf-gcc -T linker.ld -o $(BUILD_DIR)PaulOS.bin -ffreestanding -O2 -nostdlib $^ -lgcc

#$(BUILD_DIR)%.o: $(SRC_DIR)%.c
#	$(CC) -I$(SRC_DIR) -c $< -o $@ $(CFLAGS)

PaulOS.bin: $(OBJS) ./linker.ld
  $(CC) -T ./linker.ld -o $@ -ffreestanding -O2 -nostdlib $@ -lgcc

%.o: %.c
  @$(CC) -MD $(CFLAGS) -c $< -o $@


