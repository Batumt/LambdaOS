This project is developed for learning purposes, inspired by early UNIX-like systems

### Current Status (v0.5)

- Multiboot compliant kernel (GRUB)
- Basic kernel written in C
- VGA text-mode terminal driver
- Keyboard-ready TTY structure
- Minimal libc implementation:
  - string (memcpy, memmove, memset, strlen, memcmp)
  - stdio (printf, putchar, puts)
- Cross-compiled using i686-elf-gCC
- Boots successfully on QEMU

- ### Requirements
- i686-elf-gcc cross compiler
- GNU Make
- GRUB
- QEMU (for testing)

### Build
```bash
./build.sh
