#ifndef ISR_H
#define ISR_H

#include <stdint.h>

struct isr_regs {
    uint32_t int_no;     // interrupt number
    uint32_t err_code;   // 0 if no error code
    uint32_t eip;        // CPU-pushed EIP
    uint32_t cs;         // CPU-pushed CS
    uint32_t eflags;     // CPU-pushed EFLAGS
};

typedef void (*isr_t)(struct isr_regs*);

void exception_handler(struct isr_regs *r);

#endif
