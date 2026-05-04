#include <stdio.h>
#include <kernel/cmos.h>
#include <kernel/kernel.h> 
#include <stdarg.h>

int printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int written = 0;

    for (const char* p = format; *p != '\0'; p++) {
        if (*p == '%') {
            p++;
            if (*p == 'd') {
                int i = va_arg(args, int);
                if (i == 0) { putchar('0'); written++; }
                else {
                    char buf[10];
                    int len = 0;
                    while (i > 0) {
                        buf[len++] = (i % 10) + '0';
                        i /= 10;
                    }
                    while (len > 0) { putchar(buf[--len]); written++; }
                }
            } else if (*p == 's') {
                char* s = va_arg(args, char*);
                while(*s) { putchar(*s++); written++; }
            } else {
                putchar('%'); putchar(*p); written += 2;
            }
        } else {
            putchar(*p);
            written++;
        }
    }
    va_end(args);
    return written;
}
/*
 * Convert a BCD-encoded CMOS value to binary.  Most BIOSes store the clock
 * registers in BCD format.
 */
static unsigned char bcd_to_binary(unsigned char val) {
    return (val & 0x0F) + ((val >> 4) * 10);
}

/* Read a byte from the CMOS/RTC at the given register. */
unsigned char cmos_read(unsigned char reg) {
    /* mask off the NMI bit; writing the port automatically disables NMI */
    outportb(0x70, reg & 0x7F);
    return inportb(0x71);
}

/* Print a human–readable date/time string by querying the RTC. */
void get_date_string(void) {
    unsigned char second = bcd_to_binary(cmos_read(0x00));
    unsigned char minute = bcd_to_binary(cmos_read(0x02));
    unsigned char hour   = bcd_to_binary(cmos_read(0x04));
    unsigned char day    = bcd_to_binary(cmos_read(0x07));
    unsigned char month  = bcd_to_binary(cmos_read(0x08));
    unsigned char year   = bcd_to_binary(cmos_read(0x09));

    /* our printf only supports %d and %s, no padding */
    printf("\nDate: %d/%d/20%d    Time: %d:%d:%d",
           month, day, year, hour, minute, second);
}
