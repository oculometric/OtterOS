echo OtterOS Build Script Started

echo Assembling boot.s
nasm -f elf dev/src/boot.s -o boot.o

echo Compiling C++ file kernel.cc
g++ -c dev/src/kernel.cc -o kernel.o -ffreestandinng -fno-exceptions -fno-rtti

echo Linking
gcc -T linker.ld -o otterOS.bin -ffreestanding -nostdlib -nodefaultlibs boot.o kernel.o -lgcc

if grub-file --is-x86-multiboot otterOS.bin; then
  echo Confirmed otterOS.bin is multiboot
else
  echo Error! otterOS.bin is not multiboot!
fi

echo Generating ISO file
mkdir -p bin/isodir/boot/grub
mv otterOS.bin bin/isodir/boot/otterOS.bin
mv grub.cfg bin/isodir/boot/grub/grub.cfg
grub-mkrescue -o otterOS.iso bin/isodir

echo Script Finished
