all: bootloader

bootloader:
	nasm ./boot/boot.asm -f bin -o ./boot/bin/boot.bin
	nasm ./boot/kernel_entry.asm -f elf -o ./boot/bin/kernel_entry.bin
	g++ -m32 -ffreestanding -c ./boot/kernel.cpp -o ./boot/bin/kernel.o
	ld -m elf_i386 -Ttext=0x9000 ./build/kernel.ld -o ./boot/bin/kernel.img ./boot/bin/kernel_entry.bin ./boot/bin/kernel.o
	objcopy -O binary -j .text ./boot/bin/kernel.img ./boot/bin/kernel.bin
	cat ./boot/bin/boot.bin ./boot/bin/kernel.bin > ./build/os.bin
	gcc ./build/makevfs.c -o ./build/makevfs
	./build/makevfs
	cp ./build/os.bin ./release/os.bin
clean:
	rm -f ./boot/bin/boot.bin
	rm -f ./boot/bin/kernel_entry.bin
	rm -f ./boot/bin/kernel.bin
	rm -f ./boot/bin/kernel.img
	rm -f ./boot/bin/kernel.o
	rm -f ./build/os.img
	rm -rf ./iso

run:
	qemu-system-i386 -drive format=raw,file=release/os.bin -display sdl -soundhw pcspk -rtc base=localtime -netdev user,id=net0 -device virtio-net,netdev=net0
