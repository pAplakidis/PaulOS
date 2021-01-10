#!/bin/bash
export PATH="$HOME/opt/cross/bin:$PATH"
make || exit 1

grub-file --is-x86-multiboot PaulOS.bin && echo "OK"
mkdir -p isodir/boot/grub
cp PaulOS.bin isodir/boot/PaulOS.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o PaulOS.iso isodir && mv PaulOS.iso isodir/PaulOS.iso

