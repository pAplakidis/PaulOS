#!/bin/bash
QEMU_ARGS=(
          # Disable default devices
          # QEMU by default enables a ton of devices which slow down boot.
          "-nodefaults"
          # Use a standard VGA for graphics
          "-vga"
          "std"
          # Use a modern machine, with acceleration if possible.
          "-machine"
          # "q35" # also works, but slower
          # Interesting to see how this changes CPU-ID
          # Without KVM the Hypervisor is QEMU, else its KVM
          "q35,accel=kvm:tcg"
          # Allocate some memory
          "-m"
          "128M"
          # Set up OVMF
          "-drive"
          "if=pflash,format=raw,readonly,file=${OVMF_FW_PATH}"
          "-drive"
          "if=pflash,format=raw,file=${OVMF_VARS_PATH}"
          # Mount a local directory as a FAT partition
          "-drive"
          "format=raw,file=fat:rw:${QEMU_VOLUME_DIR}"
          # Enable serial
          #
          # Connect the serial port to the host. OVMF is kind enough to connect
          # the UEFI stdout and stdin to that port too.
          "-serial"
          "stdio"
          # https://qemu-project.gitlab.io/qemu/system/invocation.html
          # using this, the program can write to X86 I/O port 0xe9 and talk
          # to qemu => debug output
          "-debugcon"
          # or "/dev/stdout" => it appears in terminal window
          "/dev/stdout"
          # this is poorly documented! I found out by coincidence, that I can use a file like this
          #"file:qemu/debugcon.txt"
          # Setup monitor
          "-monitor"
          "vc:1024x768"
)

echo "Executing: qemu-system-x86_64 " "${QEMU_ARGS[@]}"
qemu-system-i386 -cdrom isodir/PaulOS.iso

