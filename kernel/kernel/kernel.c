#include <stdio.h>

#include <kernel/tty.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <kernel/pic.h>
#include <arch/i386/isr.h>

void kernel_main(void) {
    gdt_install();
    idt_init();
    PIC_remap(0x20, 0x28);
    PIC_enable();
	terminal_initialize();
	printf("Hello, kernel World!\n");
    while(1);
}
