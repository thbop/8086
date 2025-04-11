CC = gcc
ASM = nasm
CFLAGS = -g -o2 -Iinclude

NAME = emu
SRC = $(NAME).c
TARGET = $(NAME).exe

all: clean $(TARGET)

$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf $(TARGET)