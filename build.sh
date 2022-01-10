#!/bin/bash
export PATH="$HOME/opt/cross/bin:$PATH"

mkdir -p build
cd build
cmake ..
make || exit 1
#/usr/bin/ld -m elf_i686 -T../link.ld -o PaulOS.bin ./libkernel.img.a || exit 1
#i686-elf-gcc -T../linker.ld -o PaulOS.bin -ffreestanding -O2 -nostdlib ./libkernel.img.a -lgcc
echo "[+] Built image"
cd ..

if [[ -z "$1" ]]
then
  exit 0
fi

if [ $1 = "iso" ]
then
  echo "[+] Creating iso"
  grub-file --is-x86-multiboot build/PaulOS.bin && echo "OK"
  mkdir -p isodir/boot/grub
  cp build/PaulOS.bin isodir/boot/PaulOS.bin
  cp grub.cfg isodir/boot/grub/grub.cfg
  grub-mkrescue -o PaulOS.iso isodir && mv PaulOS.iso isodir/PaulOS.iso
fi

