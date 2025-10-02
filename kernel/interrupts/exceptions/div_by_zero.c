#include <stdio.h>

__attribute__((noreturn)) void divide_by_zero_handler(void)
{
    printf("Divide by zero exception!\n");
}
