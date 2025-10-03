#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

#define TTY_BUF_SIZE 128

static char tty_buf[TTY_BUF_SIZE];
static volatile int head = 0;
static volatile int tail = 0;
static volatile bool line_ready = false;

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;

void tty_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void tty_writeentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void tty_writechar(char c)
{
	unsigned char uc = c;
	if (c == '\n')
	{
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
		return;
	}
	tty_writeentryat(uc, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH)
	{
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void tty_write(const char *data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		tty_writechar(data[i]);
}

void tty_writestring(const char *data)
{
	tty_write(data, strlen(data));
}

void tty_putchar(char c)
{
	if (c == '\r')
	{
		c = '\n';
	}

	// Echo to screen (optional, depends on design)
	tty_writechar(c);

	// Store in buffer
	int next = (head + 1) % TTY_BUF_SIZE;
	if (next != tail)
	{
		tty_buf[head] = c;
		head = next;

		// Mark line ready when newline enqueued
		if (c == '\n')
		{
			line_ready = true;
		}
	}

	// If you have wait queues, wake up reader here
	// wakeup(stdin_waiters);
}

char tty_getchar()
{
	// Block until buffer has something
	while (head == tail)
	{
		// schedule(); // yield CPU until IRQ fills buffer
	}
	char c = tty_buf[tail];
	tail = (tail + 1) % TTY_BUF_SIZE;
	return c;
}

// Canonical mode: read full line until Enter pressed
int tty_getline(char *buf, int max_len)
{
	int i = 0;

	while (!line_ready)
	{
		// schedule(); // yield CPU until a full line is available
	}

	while (1)
	{
		char c = tty_getchar();
		if (c == '\r')
		{
			c = '\n';
		}

		if (c == '\b' || c == 0x7F)
		{
			if (i > 0)
			{
				i--;
			}
			continue;
		}

		if (c == '\n')
		{
			break;
		}

		if (i < max_len - 1)
		{
			buf[i++] = c;
		}
	}

	buf[i] = '\0';
	line_ready = false;
	return i;
}
