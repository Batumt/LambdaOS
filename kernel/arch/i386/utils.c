#include <kernel/kernel.h>
#include <stddef.h>

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int strcmp(const char *a, const char *b) {
    while (*a && *a == *b) {
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

void *memset(void *dest, int val, size_t n) {
    unsigned char *d = dest;
    for (size_t i = 0; i < n; i++) {
        d[i] = (unsigned char)val;
    }
    return dest;
}

unsigned char hex_to_int(char *str) {
    unsigned char result = 0;
    if (!str) return 0;
    
    while (*str) {
        unsigned char c = *str;
        result = (result << 4);
        
        if (c >= '0' && c <= '9') {
            result |= (c - '0');
        } else if (c >= 'a' && c <= 'f') {
            result |= (10 + c - 'a');
        } else if (c >= 'A' && c <= 'F') {
            result |= (10 + c - 'A');
        }
        str++;
    }
    return result;
}


unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t n) {
    for (size_t i = 0; i < n; i++) {
        dest[i] = val;
    }
    return dest;
}

void reboot(void) {
    unsigned char good = 0x02;
    while ((good & 0x02) != 0) {
        good = inportb(0x64);
    }
    outportb(0x64, 0xFE);
    
    while (1) {
        __asm__("hlt");
    }
}
