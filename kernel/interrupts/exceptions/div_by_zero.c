#include <stdio.h>
#include <arch/i386/isr.h>

__attribute__((noreturn)) void divide_by_zero_handler(struct isr_regs *r)
{
    printf("Divide by zero exception: int_no=%u, err_code=%u\n", r->int_no, r->err_code);
}
