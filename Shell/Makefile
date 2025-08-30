CC = gcc
AS = gcc   # use gcc for .S so preprocessor runs
LD = ld

CFLAGS = -nostdlib -ffreestanding -fno-builtin -Wall -Wextra
ASFLAGS =
LDFLAGS = -z noexecstack

SRC = start.S sys.S shell.c
OBJ = $(SRC:%.S=build/%.o)
OBJ := $(OBJ:%.c=build/%.o)

TARGET = build/shell

all: build $(TARGET)

build:
	mkdir -p build

$(TARGET): $(OBJ)
	$(LD) -o $@ $(OBJ) $(LDFLAGS)

build/%.o: %.S | build
	$(AS) -c $(ASFLAGS) $< -o $@

build/%.o: %.c | build
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf build
