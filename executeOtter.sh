echo Started Otter
typeset -i buildNum=$(cat logs/buildcounter)

typeset -i runNum=$(cat logs/runcounter)
echo $(($runNum+1)) > logs/runcounter

touch logs/serial/Serial-$buildNum-$runNum.log

qemu-system-i386 -cdrom OtterOS-Latest.iso -serial file:logs/serial/Serial-$buildNum-$runNum.log
echo Stopped Otter
