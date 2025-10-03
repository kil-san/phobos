#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

char *int_to_str(int value, char *str);
char *uint_to_str(unsigned int value, char *str);

static bool print(const char *data, size_t length)
{
	const unsigned char *bytes = (const unsigned char *)data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}

int printf(const char *restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0')
	{
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%')
		{
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char *format_begun_at = format++;

		if (*format == 'c')
		{
			format++;
			char c = (char)va_arg(parameters, int /* char promotes to int */);
			if (!maxrem)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		}
		else if (*format == 's')
		{
			format++;
			const char *str = va_arg(parameters, const char *);
			size_t len = strlen(str);
			if (maxrem < len)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		}
		else if (*format == 'i' || *format == 'd')
		{
			format++;
			int value = va_arg(parameters, int);
			char buf[12]; // Enough to hold 32-bit int
			int_to_str(value, buf);
			size_t len = strlen(buf);
			if (maxrem < len)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(buf, len))
				return -1;
			written += len;
		}
		   else if (*format == 'u')
		   {
			   format++;
			   unsigned int value = va_arg(parameters, unsigned int);
			   char buf[12]; // Enough to hold 32-bit unsigned int
			   uint_to_str(value, buf);
			   size_t len = strlen(buf);
			   if (maxrem < len)
			   {
				   // TODO: Set errno to EOVERFLOW.
				   return -1;
			   }
			   if (!print(buf, len))
				   return -1;
			   written += len;
		   }
		else
		{
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}

// Convert integer `value` to string in `str`.
// Returns pointer to `str`.
// No standard library used.
char *int_to_str(int value, char *str)
{
	char *p = str;
	char *p1 = str;
	char *p2;
	unsigned int abs_val;

	// Special case for INT_MIN
	if (value == INT_MIN) {
		// INT_MIN is -2147483648 for 32-bit int
		// We can't negate it directly, so handle as string
		const char *min_str = "-2147483648";
		char *s = str;
		while (*min_str) {
			*s++ = *min_str++;
		}
		*s = '\0';
		return str;
	}

	// Handle negative numbers
	if (value < 0)
	{
		*p++ = '-';
		abs_val = (unsigned int)(-value);
	}
	else
	{
		abs_val = (unsigned int)value;
	}

	// Convert number to string (in reverse order)
	do
	{
		*p++ = (char)('0' + (abs_val % 10));
		abs_val /= 10;
	} while (abs_val > 0);

	*p = '\0'; // null terminate

	// Reverse the digits (ignoring leading '-')
	if (*str == '-')
	{
		p1 = str + 1;
	}
	p2 = p - 1;

	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return str;
}

// Convert unsigned integer `value` to string in `str`.
// Returns pointer to `str`.
// No standard library used.
char *uint_to_str(unsigned int value, char *str)
{
	char *p = str;
	char *p1 = str;
	char *p2;
	// Convert number to string (in reverse order)
	do {
		*p++ = (char)('0' + (value % 10));
		value /= 10;
	} while (value > 0);
	*p = '\0';
	// Reverse the string
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
	return str;
}
