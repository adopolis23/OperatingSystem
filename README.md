
# Operating System

## Running with QEMU

when running with QEMU run with:
```
qemu-system-i386 -cdrom os.iso -monitor stdio
```
Then in terminal you can inspect registers with:
```
info registers
```

### Running with QEMU for com serial monitoring

```
qemu-system-x86_64 -serial stdio -cdrom os.iso
```

## Writing Text

Text is written to the console with the `framebuffer` which is memory mapped IO. Starting address for the framebuffer is `0x000B8000`. Character in each cell is determined by 2 bytes (8: Char, 4: Foreground, 4: Background).


## Notes

When creating structs for configuration bytes make sure packed attribute is set to avoid compiler GCC adding any padding.
```C
struct example {
unsigned char config; /* bit 0 - 7 */
unsigned short address; /* bit 8 - 23 */
unsigned char index; /* bit 24 - 31 */
} __attribute__((packed));
```

Because there is no standard lib many flags need to be used when compiling.

`required`
-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles
-nodefaultlibs

`optional`
-Wall -Wextra -Werror
