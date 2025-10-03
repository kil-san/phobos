#include <arch/i386/irq.h>
#include <kernel/pic.h>

void irq_handler(struct irq_regs *r)
{
  PIC_sendEOI(r->int_no - 32);
}
