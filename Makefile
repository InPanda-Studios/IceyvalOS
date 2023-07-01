all: bootloader

bootloader:
	nasm ./Boot/boot.asm -f bin -o ./Boot/Bin/boot.bin
	nasm ./Boot/kernel_entry.asm -f elf -o ./Boot/Bin/kernel_entry.bin
	g++ -m32 -ffreestanding -c ./Boot/kernel.cpp -o ./Boot/Bin/kernel.o
	ld -m elf_i386 -Ttext=0x9000 ./Build/kernel.ld -o ./Boot/Bin/kernel.img ./Boot/Bin/kernel_entry.bin ./Boot/Bin/kernel.o
	objcopy -O binary -j .text ./Boot/Bin/kernel.img ./Boot/Bin/kernel.bin
	cat ./Boot/Bin/boot.bin ./Boot/Bin/kernel.bin > ./Build/os.bin
	gcc ./Build/makevfs.c -o ./Build/makevfs
	./Build/makevfs
	cp ./Build/os.bin ./Release/os.bin
clean:
	rm -r ./Boot/Bin/
	rm -f ./Build/os.img
run:
	qemu-system-i386 -drive format=raw,file=Release/os.bin -display sdl -soundhw pcspk -rtc base=localtime -netdev user,id=net0 -device virtio-net,netdev=net0
