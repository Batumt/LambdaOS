#include <kernel/scrn.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/irq.h>
#include <kernel/isrs.h>

#include <kernel/cmos.h>
#include <kernel/kb.h>
#include <kernel/shell.h>
#include <kernel/timer.h>

void kernel_main(void) {
    terminal_initialize(); 
    
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    
    timer_install();
    keyboard_install();
    
    __asm__ __volatile__ ("sti");

    shell_init(); 

    while(1) {
        __asm__ __volatile__ ("hlt");
    }
}