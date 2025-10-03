#include <stdint.h>

struct irq_regs
{
  uint32_t int_no;
  uint32_t err_code;
};

void irq_handler(struct irq_regs *r);
