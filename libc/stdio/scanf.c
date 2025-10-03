#include <stdio.h>
#include <kernel/tty.h>

int scanf(const char *fmt, void *out)
{
	if (fmt[0] == '%' && fmt[1] == 's')
	{
		return tty_getline((char *)out, 128); // simple example
	}
	// expand for %d, %c, etc.
	return 0;
}
