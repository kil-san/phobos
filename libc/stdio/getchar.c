#include <kernel/tty.h>

int getchar()
{
	return tty_getchar();
}
