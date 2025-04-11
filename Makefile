CC = gcc
ASM = nasm
CFLAGS = -g -o2 -Iinclude

NAME = emu
SRC = $(NAME).c
TARGET = $(NAME).exe

BUILD_DIR = build
SRC_DIR = src

.PHONY: all clean emu tests

all: clean emu tests

emu:
	$(CC) $(CFLAGS) $(SRC) -o $(BUILD_DIR)/$(TARGET)

tests:
	$(MAKE) -C $(SRC_DIR)/tests BUILD_DIR=$(abspath $(BUILD_DIR))

clean:
	rm -rf $(BUILD_DIR)/*