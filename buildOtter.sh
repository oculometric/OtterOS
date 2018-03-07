echo OtterOS Build Script Started

echo Assembling boot.s
nasm -felf32 dev/src/boot.asm -o dev/bin/boot.o

echo Compiling C++ file kernel.cc
g++ -c dev/src/kernel.cc -o dev/bin/kernel.o -ffreestanding -fno-exceptions -fno-rtti

cd dev/bin/

echo Linking
gcc -T ../src/linker.ld -o otterOS.bin -ffreestanding -nostdlib -nodefaultlibs boot.o kernel.o -lgcc

if grub-file --is-x86-multiboot otterOS.bin; then
  echo Confirmed otterOS.bin is multiboot
else
  echo Error! otterOS.bin is not multiboot!
fi

echo Generating ISO file
mkdir -p isodir/boot/grub
cp otterOS.bin isodir/boot/otterOS.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o otterOS.iso isodir

echo Script Finished
