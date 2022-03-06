#/bin/bash
export PATH="$HOME/opt/cross/bin:$PATH"

#mkdir -p build
#i686-elf-as src/boot.s -o boot.o  || exit 1  # TODO: this is temporary
#cd build
#cmake ..
make || exit 1
#cat boot.o PaulOS.bin > PaulOS.bin
echo "[+] Built image"
cd ..

if [[ -z "$1" ]]
then
  exit 0
fi

if [ $1 = "iso" ]
then
  echo "[+] Creating iso"
  
  if grub-file --is-x86-multiboot build/PaulOS.bin; then
    echo "[+] Multiboot Confirmed"
  else
    echo "[-] ERROR: File is not multiboot!"
    exit 1
  fi
  
  mkdir -p isodir/boot/grub
  cp build/PaulOS.bin isodir/boot/PaulOS.bin
  cp grub.cfg isodir/boot/grub/grub.cfg
  grub-mkrescue -o PaulOS.iso isodir && mv PaulOS.iso isodir/PaulOS.iso
fi

