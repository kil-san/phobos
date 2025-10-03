#include <arch/i386/isr.h>
#include <kernel/ports.h>
#include <stdbool.h>
#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/keyboard.h>

static const char scancode_set1[128] = {
  [0x01] = 27,
  [0x02] = '1',
  [0x03] = '2',
  [0x04] = '3',
  [0x05] = '4',
  [0x06] = '5',
  [0x07] = '6',
  [0x08] = '7',
  [0x09] = '8',
  [0x0A] = '9',
  [0x0B] = '0',
  [0x0C] = '-',
  [0x0D] = '=',
  [0x0E] = '\b',
  [0x0F] = '\t',
  [0x10] = 'q',
  [0x11] = 'w',
  [0x12] = 'e',
  [0x13] = 'r',
  [0x14] = 't',
  [0x15] = 'y',
  [0x16] = 'u',
  [0x17] = 'i',
  [0x18] = 'o',
  [0x19] = 'p',
  [0x1A] = '[',
  [0x1B] = ']',
  [0x1C] = '\n',
  [0x1E] = 'a',
  [0x1F] = 's',
  [0x20] = 'd',
  [0x21] = 'f',
  [0x22] = 'g',
  [0x23] = 'h',
  [0x24] = 'j',
  [0x25] = 'k',
  [0x26] = 'l',
  [0x27] = ';',
  [0x28] = '\'',
  [0x29] = '`',
  [0x2B] = '\\',
  [0x2C] = 'z',
  [0x2D] = 'x',
  [0x2E] = 'c',
  [0x2F] = 'v',
  [0x30] = 'b',
  [0x31] = 'n',
  [0x32] = 'm',
  [0x33] = ',',
  [0x34] = '.',
  [0x35] = '/',
  [0x37] = '*',
  [0x39] = ' ',
};

static const char scancode_set1_shift[128] = {
  [0x02] = '!',
  [0x03] = '@',
  [0x04] = '#',
  [0x05] = '$',
  [0x06] = '%',
  [0x07] = '^',
  [0x08] = '&',
  [0x09] = '*',
  [0x0A] = '(',
  [0x0B] = ')',
  [0x0C] = '_',
  [0x0D] = '+',
  [0x1A] = '{',
  [0x1B] = '}',
  [0x27] = ':',
  [0x28] = '"',
  [0x29] = '~',
  [0x2B] = '|',
  [0x33] = '<',
  [0x34] = '>',
  [0x35] = '?',
};

static bool shift_pressed = false;
static bool caps_lock_active = false;

void keyboard_event_processor(void)
{
  uint8_t scancode = inb(0x60);

  if (scancode & 0x80)
  {
    uint8_t released = scancode & 0x7F;
    if (released == 0x2A || released == 0x36)
    {
      shift_pressed = false;
    }
    return;
  }

  if (scancode == 0x2A || scancode == 0x36)
  {
    shift_pressed = true;
    return;
  }

  if (scancode == 0x3A)
  {
    caps_lock_active = !caps_lock_active;
    return;
  }

  char c = scancode_set1[scancode];
  if (!c)
  {
    return;
  }

  if (c >= 'a' && c <= 'z')
  {
    bool uppercase = shift_pressed ^ caps_lock_active;
    if (uppercase)
    {
      c = c - ('a' - 'A');
    }
  }
  else if (shift_pressed)
  {
    char shifted = scancode_set1_shift[scancode];
    if (shifted)
    {
      c = shifted;
    }
  }

  tty_putchar(c);
}
