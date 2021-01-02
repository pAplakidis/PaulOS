#!/bin/bash
export PATH="$HOME/opt/cross/bin:$PATH"
make

grub-file --is-x86-multiboot myos.bin && echo "OK"
mkdir -p isodir/boot/grub
cp myos.bin isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir && mv myos.iso isodir/myos.iso

