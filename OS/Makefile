# Makefile

# Tools and flags
AS = nasm
ASFLAGS = -f elf32
LD = ld
LDFLAGS = -T link.ld -melf_i386

# Files and directories
SRC = loader.s
BUILD_DIR = build
OBJ = $(BUILD_DIR)/loader.o
KERNEL = $(BUILD_DIR)/kernel.elf

# Default target
all: $(KERNEL)

# Linking
$(KERNEL): $(OBJ) link.ld
	$(LD) $(LDFLAGS) $(OBJ) -o $@

# Assembling
$(OBJ): $(SRC) | $(BUILD_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

#wget -O stage2_eltorito https://github.com/littleosbook/littleosbook/raw/master/files/stage2_eltorito
iso:
	cp stage2_eltorito iso/boot/grub
	cp build/kernel.elf iso/boot/
