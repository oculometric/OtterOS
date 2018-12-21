echo Started Otter
typeset -i buildNum=$(cat logs/buildcounter)

typeset -i runNum=$(cat logs/runcounter)
echo $(($runNum+1)) > logs/runcounter

touch logs/serial/Serial-$buildNum-$runNum.log
if [ $1 = "debug" ]
then
  echo "I'm ready, now start GDB with \`target remote localhost:1234\`"
  qemu-system-i386 -cdrom OtterOS-Latest.iso -serial file:logs/serial/Serial-$buildNum-$runNum.log -d guest_errors -s
else
  echo "Starting normally"
  qemu-system-i386 -cdrom OtterOS-Latest.iso -serial file:logs/serial/Serial-$buildNum-$runNum.log
fi

echo Stopped Otter
