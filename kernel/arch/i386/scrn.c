#include <kernel/scrn.h>
#include <kernel/irq.h>
#include <kernel/kernel.h>
#include <stdint.h>
#include <kernel/kernel.h>

unsigned short *textmemptr = (unsigned short *) 0xB8000;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

void terminal_write(const char* data, size_t size){
    for (size_t i = 0; i < size; i++)
    terminal_putchar(data[i]);
}

void scroll(void){
    unsigned blank, temp;

    blank = 0x20 | (attrib << 8);

    if (csr_y >= 25){
        temp = csr_y - 25 +1;
        memcpy (textmemptr, textmemptr + temp *80, (25 - temp) * 80 *2);
        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 -1;
    }
}

void move_csr(void){
    unsigned temp;
    temp = csr_y * 80 +csr_x;
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}


void cls() {
    unsigned short blank = 0x20 | (attrib << 8);
    int i;
    for(i = 0; i < 25; i++) {
        memsetw(textmemptr + i * 80, blank, 80);
    }

    csr_x = 0;
    csr_y = 0;
    move_csr();
}

void terminal_putchar(char c){
    unsigned short *where;
    unsigned att = attrib << 8;

    if(c == 0x08){
        if(csr_x != 0) csr_x--;
    }

    else if(c == 0x09){
        csr_x = (csr_x + 8) & ~ (8 - 1);
    }
    
    else if (c == '\r'){
        csr_x = 0;
    }

    else if (c == '\n'){
        csr_x = 0;
        csr_y++;
    }

    else if(c >=  ' '){
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;
        csr_x++;
    }

    if(csr_x >= 80){
        csr_x = 0;
        csr_y++;
    }
    scroll();
    move_csr();
}

void terminal_initialize(){
    textmemptr = (unsigned short *)0xB8000;
    cls();
}

void putch(char c){
    terminal_putchar(c);
}

void putch_backspace(){
    if (csr_x > 0){
        csr_x--;
        unsigned short *where = textmemptr + (csr_y * 80 + csr_x);
        *where = 0x20 | (attrib << 8);
    }
    move_csr();
}

void set_screen_attrib(unsigned char color_byte){
    attrib = color_byte;
}