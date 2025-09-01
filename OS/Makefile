# Makefile

# Tools and flags
AS = nasm
ASFLAGS = -f elf32
LD = ld
CC = gcc
LDFLAGS = -T src/link.ld -melf_i386
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs

# Files and directories
AS_SRC = src/loader.s
AS_OBJ = $(BUILD_DIR)/loader.o

C_SRC = src/kmain.c
C_OBJ = $(BUILD_DIR)/kmain.o

OBJS = $(AS_OBJ) $(C_OBJ)

BUILD_DIR = build

KERNEL = $(BUILD_DIR)/kernel.elf
ISO = os.iso





# Default target (build kernel)
all: $(KERNEL)

# Linking
$(KERNEL): $(OBJS) src/link.ld
	$(LD) $(LDFLAGS) $(OBJS) -o $@

# Assembling
$(AS_OBJ): $(AS_SRC) | $(BUILD_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Compiling C
$(C_OBJ): $(C_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build ISO
$(ISO): stage2_eltorito $(KERNEL)
	mkdir -p iso/boot/grub
	cp stage2_eltorito iso/boot/grub/
	cp $(KERNEL) iso/boot/kernel.elf

	genisoimage -R \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot \
		-boot-load-size 4 \
		-A os \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o $@ \
		iso

# Convenience alias
iso: $(ISO)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -rf iso/boot/kernel.elf
	rm -f $(ISO)
