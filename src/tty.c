/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2024  Arka Mondal
*/

#include "string.h"
#include "tty.h"

static size_t tty_row;
static size_t tty_col;
static uint8_t tty_color;
static uint16_t * tty_buffer;

static inline uint8_t vga_entry_color(vga_color_t fg, vga_color_t bg)
{
  return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
  return (uint16_t) uc | (uint16_t) color << 8;
}

void tty_init(void)
{
  size_t x, y, index;

  tty_row = 0;
  tty_col = 0;
  tty_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  tty_buffer = (uint16_t *) 0xb8000;

  for (y = 0; y < VGA_HIGHT; y++)
  {
    for (x = 0; x < VGA_WIDTH; x++)
    {
      index = y * VGA_WIDTH + x;
      tty_buffer[index] = vga_entry(' ', tty_color);
    }
  }
}

void tty_setcolor(uint8_t color)
{
  tty_color = color;
}

void tty_putat(char c, uint8_t color, size_t x, size_t y)
{
  size_t index;

  index = y * VGA_WIDTH + x;
  tty_buffer[index] = vga_entry(c, color);
}

void tty_putchar(char c)
{
  if ((c != '\n') && (c != '\r'))
  {
    tty_putat(c, tty_color, tty_col, tty_row);
    tty_col++;
  }
  else
  {
    tty_col = VGA_WIDTH;
  }

  if (tty_col == VGA_WIDTH)
  {
    tty_col = 0;
    tty_row++;
    if (tty_row == VGA_HIGHT)
      tty_row = 0;
  }
}

void tty_write(const char * data, size_t size)
{
  size_t i;

  for (i = 0; i < size; i++)
    tty_putchar(data[i]);
}

void tty_writestr(const char * str)
{
  size_t len;

  len = strlen(str);

  tty_write(str, len);
}
