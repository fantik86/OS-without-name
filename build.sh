nasm -f elf boot.asm -o boot.o
gcc -I ./include/ -std=gnu99 -masm=intel -m32 -ffreestanding -fno-pic -c kernel.c -o kernel.o
ld -m elf_i386 -T linker.ld -o kernel.elf boot.o kernel.o 
objcopy -O binary kernel.elf boot.bin
mkisofs -R -b boot.bin -no-emul-boot -boot-load-size 4 -o os.iso ./
cmd.exe /C "C:\Program Files\qemu\qemu-system-i386" -monitor stdio -cdrom os.iso
