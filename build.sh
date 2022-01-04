#!/bin/bash
export PATH="$HOME/opt/cross/bin:$PATH"

# TODO: this is a temp hack, need to do this in CMake
#i686-elf-as src/boot.s -o boot.o
#echo "[+] Bootloader done"

mkdir -p build
cd build
cmake ..
make || exit 1
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

