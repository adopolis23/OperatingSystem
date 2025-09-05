# Tools and flags
AS = nasm
ASFLAGS = -f elf32
LD = ld
CC = gcc
LDFLAGS = -T src/link.ld -melf_i386
CFLAGS = -m32 -nostdlib -nostdinc -ffreestanding -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs


# directories
BUILD_DIR = build
SRC_DIR = src

# Files
AS_SRC = $(SRC_DIR)/loader.s $(SRC_DIR)/io/io.s $(SRC_DIR)/utility/utility.s
AS_OBJ = $(AS_SRC:$(SRC_DIR)/%.s=$(BUILD_DIR)/%.o)

C_SRC = $(SRC_DIR)/kmain.c $(SRC_DIR)/io/io_c.c $(SRC_DIR)/utility/utility_c.c
C_OBJ = $(C_SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

OBJS = $(AS_OBJ) $(C_OBJ)

KERNEL = $(BUILD_DIR)/kernel.elf
ISO = os.iso

# Default target (build kernel)
all: $(KERNEL)

# Linking
$(KERNEL): $(OBJS) src/link.ld
	$(LD) $(LDFLAGS) $(OBJS) -o $@

# Assemble rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

# Compile C rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


#wget -O stage2_eltorito https://github.com/littleosbook/littleosbook/raw/master/files/stage2_eltorito
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
