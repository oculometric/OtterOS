echo OtterOS Build Script Started

typeset -i buildNum=$(cat logs/buildcounter)
DATE=`date +%d-%m-%Y`
fileName=$buildNum

echo Assembling boot.s
i686-elf-as deve/src/asm/boot.s -o deve/bin/o/boot.o
#i686-elf-as deve/src/int32.s -o deve/bin/o/int32.o
if [ ! $? -eq 0 ]; then
	exit 1
fi

echo Searching for source files
for file in deve/src/cpp/*.cc
do
	echo Compiling C++ source file $file
	name=`echo "$file" | cut -d'.' -f1`
	name=`basename $name`
	i686-elf-g++ -c $file -o deve/bin/o/$name.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -w #-ggdb
	if [ ! $? -eq 0 ]; then
		exit 1
	fi
done

cd deve/bin/

echo Linking
i686-elf-gcc -T ../src/linker.ld -o bin/otterOS.bin -ffreestanding -O2 -nostdlib -nodefaultlibs o/*.o -lgcc -Wl,--build-id=none
if [ ! $? -eq 0 ]; then
	exit 1
fi

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
#i686-elf-objcopy --only-keep-debug bin/otterOS.bin kernel.o
#i686-elf-objcopy --strip-debug bin/otterOS.bin
cp iso/otterOS-$fileName.iso ../../OtterOS-Latest.iso

echo Script Finished
cd ../..
echo $(($buildNum+1)) > logs/buildcounter
