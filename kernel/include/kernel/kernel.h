#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>
#include <stdint.h>

extern void *memcpy(void *dest, const void *src, size_t);
extern void *memset(void *dest, int val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern unsigned char inportb(unsigned short _port);
extern void outportb(unsigned short _port, unsigned char _data);
extern void reboot(void);

#endif