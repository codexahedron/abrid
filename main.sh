sources=$(find ./kernel/* -type f -name "*.c")
objects=$(echo ${sources//\.c/.o})
objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${objects}")
end=$((end+1))
# echo $List | awk '{print $2}'
nasm -f elf ./boot/boot.asm -o ./bin/boot.o

for i in $(seq 1 $end); do 
	ta=$(echo ./bin/$(basename $(echo $objects | cut -d" " -f$i )))
	tb=$(echo $sources | cut -d" " -f$i)
	objb="${objb} ${ta}"
	gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./kernel/include -fno-stack-protector -c -o $ta $tb
done
objb="${objb:1}"
ld -T link.ld -m elf_i386 -o os.bin $objb ./bin/boot.o
rm -r iso
mkdir iso
mkdir iso/boot
mkdir iso/boot/grub
ls
cp os.bin iso/boot/
./initrdgen readme readme ./kernel/* ./kernel/* ./kernel/lib/* ./kernel/lib/* ./kernel/include/* ./kernel/include/* ./boot/* ./boot/*
#./initrdgen helloworld.c helloworld.c
mv ./initrd.img ./iso/boot/os.initrd
echo 'set timeout-0' >> iso/boot/grub/grub.cfg
echo 'set default-0' >> iso/boot/grub/grub.cfg
echo 'menuentry "abrid" {' >> iso/boot/grub/grub.cfg
echo '  multiboot /boot/os.bin' >> iso/boot/grub/grub.cfg
echo '  module  /boot/os.initrd' >> iso/boot/grub/grub.cfg
echo '  boot' >> iso/boot/grub/grub.cfg
echo '}' >> iso/boot/grub/grub.cfg
grub-mkrescue --output=os.iso iso
#qemu-system-i386 -kernel os.bin -initrd initrd.img -hda floppy.img -m 128M -machine type=pc-i440fx-3.1
qemu-system-i386 -cdrom os.iso -m 256M -hda floppy.img