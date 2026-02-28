#include <stdio.h>           

#include <kernel/kernel.h>   
#include <kernel/scrn.h>     
#include <kernel/cmos.h>
#include <kernel/irq.h>

unsigned char bcd_to_bin(unsigned char bcd){
    return ((bcd /16) * 10) + (bcd %16);
}

unsigned char cmos_read(unsigned char reg){
    outportb(0x70, reg);
    return inportb(0x71);
}

void get_date_string() {
    
    unsigned char minute = bcd_to_bin(cmos_read(0x02));
    unsigned char hour = bcd_to_bin(cmos_read(0x04));
    unsigned char day = bcd_to_bin(cmos_read(0x07));
    unsigned char month = bcd_to_bin(cmos_read(0x08));
    unsigned char year = bcd_to_bin(cmos_read(0x09));

    printf("\nTime: %d%d:%d%d\n", 
        (hour / 10), (hour % 10),
        (minute / 10), (minute % 10));
    
    printf("Date: %d%d/%d%d/20%d%d\n",
        (day / 10), (day % 10),
        (month / 10), (month % 10), 
        (year / 10), (year % 10));
}

