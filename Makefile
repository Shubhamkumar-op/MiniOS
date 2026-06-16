ISO=MiniOS.iso

all: $(ISO)

build/kernel.bin:
	mkdir -p build

	nasm -f elf32 boot/boot.asm -o build/boot.o

	gcc -m32 -ffreestanding -c kernel/kernel.c -o build/kernel.o

	gcc -m32 -ffreestanding -c kernel/terminal.c -o build/terminal.o

	gcc -m32 -ffreestanding -c kernel/keyboard.c -o build/keyboard.o

	gcc -m32 -ffreestanding -c kernel/shell.c -o build/shell.o

	ld -m elf_i386 -T linker.ld -o build/kernel.bin \
	build/boot.o \
	build/kernel.o \
	build/terminal.o \
	build/keyboard.o \
	build/shell.o 

$(ISO): build/kernel.bin
	mkdir -p iso/boot/grub

	cp build/kernel.bin iso/boot/kernel.bin
	cp boot/grub.cfg iso/boot/grub/grub.cfg

	grub-mkrescue -o $(ISO) iso

run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -rf build iso $(ISO)