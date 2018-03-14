echo OtterOS Build Script Started

typeset -i buildNum=$(cat logs/buildcounter)
echo $(($buildNum+1)) > logs/buildcounter
DATE=`date +%d-%m-%Y`
fileName=$buildNum

echo Assembling boot.s
i686-elf-as dev/src/boot.s -o dev/bin/o/boot.o
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

echo Compiling C++ source file dev/src/kernel.cc
i686-elf-g++ -c dev/src/kernel.cc -o dev/bin/o/kernel.o -ffreestanding -O2 -fno-exceptions -fno-rtti # -masm=intel
if [ ! $? -eq 0 ]; then
	exit 1
fi

cd dev/bin/

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
