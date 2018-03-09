echo OtterOS Build Script Started

typeset -i buildNum=$(cat logs/buildcounter)
echo $(($buildNum+1)) > logs/buildcounter
DATE=`date +%d-%m-%Y`
fileName=$DATE"."$buildNum

echo Assembling boot.s
i686-elf-as dev/src/boot.s -o dev/bin/o/boot.o

#echo Compiling C++ file kernel.cc
#i686-elf-g++ -c dev/src/kernel.cc -o dev/bin/o/kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

echo Searching for source files
for file in dev/src/*.cc
do
 echo Compiling C++ source file $file
 name=`echo "$file" | cut -d'.' -f1`
 i686-elf-g++ -c dev/src/$file -o dev/bin/o/$name.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
done

cd dev/bin/

echo Linking
i686-elf-gcc -T ../src/linker.ld -o bin/otterOS.bin -ffreestanding -O2 -nostdlib -nodefaultlibs o/boot.o o/kernel.o -lgcc

if grub-file --is-x86-multiboot bin/otterOS.bin; then
  echo Confirmed otterOS.bin is multiboot
else
  echo Error! otterOS.bin is not multiboot!
	exit 1
fi

echo Generating ISO file
#mkdir -p isodir/boot/grub
cp bin/otterOS.bin isodir/boot/otterOS.bin
#cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o iso/otterOS-$fileName.iso isodir

echo Script Finished
