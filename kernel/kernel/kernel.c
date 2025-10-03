#include <stdio.h>

#include <kernel/tty.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <kernel/pic.h>
#include <arch/i386/isr.h>

void kernel_main(void)
{
    gdt_install();
    idt_init();
    PIC_remap(0x20, 0x28);
    PIC_enable();
    tty_initialize();
    printf("Enter your name: ");
    char name[128];
    scanf("%s", name);
    printf("Hello %s, welcome to kernel World\n", name);
    while (1);
}
