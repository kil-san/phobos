#ifndef _PIC_H
#define _PIC_H

#include <stdint.h>

void PIC_remap(int offset1, int offset2);
void PIC_sendEOI(uint8_t irq);
void PIC_enable();

#endif // _PIC_H
