ARCHDIR=arch/i386

include $(ARCHDIR)/make.config

CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude -I$(SYSROOT)/usr/include
LDFLAGS:=$(LDFLAGS)
LIBS:=-nostdlib $(SYSROOT)/usr/lib/libk.a -lgcc



CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/kernel.o \
kernel/kb.o \
kernel/shell.o \
kernel/timer.o \
kernel/cmos.o

OBJS=\
$(KERNEL_OBJS)

LINK_LIST=\
$(LDFLAGS) \
$(KERNEL_OBJS) \
$(LIBS)

.PHONY: all clean install install-headers install-kernel

.SUFFIXES: .o .c .S .asm

all: LambdaOS.kernel

LambdaOS.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(CPPFLAGS) -no-pie $(LINK_LIST)
	grub-file --is-x86-multiboot LambdaOS.kernel



.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.asm.o:
	nasm -felf32 $< -o $@

clean:
	rm -f LambdaOS.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: LambdaOS.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp LambdaOS.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)