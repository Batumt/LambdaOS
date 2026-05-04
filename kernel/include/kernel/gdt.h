#ifndef GDT_H
#define GDT_H

extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char acces, unsigned char gran);
extern void gdt_install();

#endif