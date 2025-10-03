#include <arch/i386/isr.h>
#include <stdio.h>

__attribute__((noreturn)) void exception_handler(struct isr_regs *r)
{
  printf("Exception triggered, int_no=%u, error_code=%u, eip=%u, cs=%u, eflags=%u\n", r->int_no, r->err_code, r->eip, r->cs, r->eflags);
  __asm__ volatile("cli; hlt"); // Completely hangs the computer
}
