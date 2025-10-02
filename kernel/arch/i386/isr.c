#include <arch/i386/isr.h>
#include <stdio.h>

__attribute__((noreturn)) void exception_handler()
{
  printf("Exception occurred!\n");
  __asm__ volatile("cli; hlt"); // Completely hangs the computer
}
