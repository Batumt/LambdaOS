#ifndef SCRN_H
#define SCRN_H

#include <stddef.h>
#include <stdint.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);

void set_screen_attrib(uint8_t color);
void cls(void);

void putch(char c);
void putch_backspace(void);

#endif