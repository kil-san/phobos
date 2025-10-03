#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void tty_initialize(void);
void tty_writechar(char c);
void tty_write(const char* data, size_t size);
void tty_writestring(const char* data);

void tty_putchar(char c);        // called by keyboard driver
char tty_getchar();              // blocking getchar
int  tty_getline(char* buf, int max_len); // blocking line input

#endif
