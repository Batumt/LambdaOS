HOSTARCH := i386

export CC := gcc -m32 --sysroot=$(shell pwd)/sysroot -ffreestanding -nostdinc -isystem $(shell gcc -m32 -print-file-name=include)
export AR := ar
export AS := as --32

export SYSROOT := $(shell pwd)/sysroot
export PREFIX := /usr
export INCLUDEDIR := $(PREFIX)/include
export LIBDIR := $(PREFIX)/lib
export BOOTDIR := /boot

.PHONY: all clean headers build iso prepare qemu run

all: iso

prepare:
	mkdir -p "$(SYSROOT)"

headers: prepare
	$(MAKE) -C libc install-headers DESTDIR=$(SYSROOT) INCLUDEDIR=$(INCLUDEDIR)
	$(MAKE) -C kernel install-headers DESTDIR=$(SYSROOT) INCLUDEDIR=$(INCLUDEDIR)

build: headers
	$(MAKE) -C libc install DESTDIR=$(SYSROOT) INCLUDEDIR=$(INCLUDEDIR) LIBDIR=$(LIBDIR)
	$(MAKE) -C kernel install DESTDIR=$(SYSROOT) INCLUDEDIR=$(INCLUDEDIR) BOOTDIR=$(BOOTDIR)

iso: build
	mkdir -p isodir/boot/grub
	cp $(SYSROOT)$(BOOTDIR)/LambdaOS.kernel isodir/boot/LambdaOS.kernel
	printf "menuentry \"LambdaOS\" {\n    multiboot /boot/LambdaOS.kernel\n}\n" > isodir/boot/grub/grub.cfg
	grub-mkrescue -o LambdaOS.iso isodir

clean:
	$(MAKE) -C libc clean
	$(MAKE) -C kernel clean
	rm -rf sysroot isodir LambdaOS.iso

qemu: iso
	qemu-system-i386 -cdrom LambdaOS.iso

run: qemu