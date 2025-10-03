#include <arch/i386/irq.h>
#include <kernel/ports.h>
#include <stdio.h>
#include <kernel/keyboard.h>
#include <kernel/pic.h>

void keyboard_handler(struct irq_regs *r)
{
  keyboard_event_processor();
  PIC_sendEOI(r->int_no - 32);
  return;
}
