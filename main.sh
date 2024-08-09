sources=$(find ./kernel/* -type f -name "*.c")
headers=$(find ./kernel/* -type f -name "*.h")
objects=$(echo ${sources//\.c/.o})
objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${objects}")
end=$((end+1))
nasm -f elf ./kernel/arch/i386/boot.asm -o ./bin/boot.o
for i in $(seq 1 $end); do 
ta=$(echo ./bin/$(basename $(echo $objects | cut -d" " -f$i )))
tb=$(echo $sources | cut -d" " -f$i)
objb="${objb} ${ta}"
gcc -m32 -elf_i386 -O -w -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./kernel/modules/include -fno-stack-protector -c -o $ta $tb
done
objb="${objb:1}"
ld -T link.ld -m elf_i386 -o os.bin $objb ./bin/boot.o
rm -r iso
mkdir iso
mkdir iso/boot
mkdir iso/boot/grub
mv os.bin iso/boot/os.bin
echo 'set timeout-0' >> iso/boot/grub/grub.cfg
echo 'set default-0' >> iso/boot/grub/grub.cfg
echo 'menuentry "abrid" {' >> iso/boot/grub/grub.cfg
echo '  multiboot /boot/os.bin' >> iso/boot/grub/grub.cfg
echo '  module  /boot/os.initrd' >> iso/boot/grub/grub.cfg
echo '  boot' >> iso/boot/grub/grub.cfg
echo '}' >> iso/boot/grub/grub.cfg
rm initrdgen
gcc initrdgen.c -o initrdgen
inp="./readme.txt ${sources} ${headers}"
res=''
for word in $inp; do
res="${res} ${word}"
res="${res} ${word}"
done
./initrdgen $res ./SYSINFO ./SYSINFO
mv ./initrd.img ./iso/boot/os.initrd
grub-mkrescue --output=os.iso iso
qemu-system-i386 -cdrom os.iso -m 480M -hda floppy.img