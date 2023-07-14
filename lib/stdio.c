/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2023  Arka Mondal
*/

#include "../include/stdio.h"
#include "../include/tty.h"

static void itoa(char * buf, int base, int d)
{
  char * p, * p1, * p2, tmp;
  int divisor, remainder;
  unsigned long ud;

  p = buf;
  divisor = 10;
  ud = d;

  if ((base == 'd') && (d < 0))
  {
    *p++ = '-';
    buf++;
    ud = -d;
  }
  else if ((base == 'x') || (base == 'p'))
    divisor = 16;

  do
  {
    remainder = ud % divisor;
    *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
  } while (ud /= divisor);

  *p = 0;

  p1 = buf;
  p2 = p - 1;
  while (p1 < p2)
  {
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
    p1++;
    p2--;
  }
}

void printf(const char * restrict format, ...)
{
  char ** arg, buf[32], * p, * p2;
  int c, pad0, pad;

  pad0 = 0;
  pad = 0;
  arg = (char **) &format;
  arg++;

  while ((c = *format++) != 0)
  {
    if (c != '%')
      tty_putchar(c);
    else
    {
      c = *format++;
      if (c == '0')
      {
        pad0 = 1;
        c = *format++;
      }

      if ((c >= '0') && (c <= '9'))
      {
        pad = c  - '0';
        c = *format++;
      }

      switch (c)
      {
        case 'd':
        case 'u':
        case 'x':
        case 'p':
          itoa(buf, c, *((int *) arg++));
          p = buf;
          goto string;
          break;

        case 's':
          p = *arg++;
          if (!p)
            p = "(null)";

        string:
          for (p2 = p; *p2; p2++)
            continue;
          for (; p2 < p + pad; p2++)
            tty_putchar(pad0 ? '0' : ' ');
          while (*p)
            tty_putchar(*p++);
          break;

        default:
          tty_putchar(*((int *) arg++));
          break;
      }
    }
  }
}
