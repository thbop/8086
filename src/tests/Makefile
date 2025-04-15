ASM ?= nasm
BUILD_DIR ?= build

all: helloworld main

helloworld:
	$(ASM) helloworld.asm -f bin -o $(BUILD_DIR)/helloworld.bin

main:
	dd if=/dev/zero of=$(BUILD_DIR)/main.bin bs=512 count=1
	dd if=$(BUILD_DIR)/helloworld.bin of=$(BUILD_DIR)/main.bin conv=notrunc

