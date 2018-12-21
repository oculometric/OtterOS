echo OtterOS Build Script Started

typeset -i buildNum=$(cat logs/buildcounter)
DATE=`date +%d-%m-%Y`
fileName=$buildNum

echo Assembling assembly files
i686-elf-as deve/src/boot.s -o deve/bin/o/boot.o
#i686-elf-as deve/src/int32.s -o deve/bin/o/int32.o
if [ ! $? -eq 0 ]; then
	exit 1
fi

# oPaths=“”
# echo Searching for source files
# for file in dev/src/include/*.cc
# do
# 	echo Compiling C++ source file $file
# 	name=`echo "$file" | cut -d'.' -f1`
# 	name=`basename $name`
# 	i686-elf-g++ -c $file -o dev/bin/o/$name.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
# 	if [ ! $? -eq 0 ]; then
# 		exit 1
# 	fi
#  #oPaths=o/$file.o $oPaths
# done

echo Compiling C++ source file deve/src/kernel.cc
i686-elf-g++ -g -c deve/src/kernel.cc -o deve/bin/o/kernel.o -ffreestanding -O2 -fno-exceptions -fno-rtti -w #-Wno-write-strings -Wno-pointer-arith # -masm=intel
if [ ! $? -eq 0 ]; then
	exit 1
fi

cd deve/bin/

echo Linking
i686-elf-gcc -T ../src/linker.ld -o bin/otterOS.bin -ffreestanding -O2 -nostdlib -nodefaultlibs o/boot.o o/kernel.o -lgcc -Wl,--build-id=none
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
cp iso/otterOS-$fileName.iso ../../OtterOS-Latest.iso

echo Script Finished
cd ../..
echo $(($buildNum+1)) > logs/buildcounter
