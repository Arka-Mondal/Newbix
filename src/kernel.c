/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2023  Arka Mondal
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#define VGA_WIDTH 80
#define VGA_HIGHT 25

typedef enum {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE,
  VGA_COLOR_GREEN,
  VGA_COLOR_CYAN,
  VGA_COLOR_RED,
  VGA_COLOR_MAGENTA,
  VGA_COLOR_BROWN,
  VGA_COLOR_LIGHT_GREY,
  VGA_COLOR_DARK_GREY,
  VGA_COLOR_LIGHT_BLUE,
  VGA_COLOR_LIGHT_GREEN,
  VGA_COLOR_LIGHT_CYAN,
  VGA_COLOR_LIGHT_RED,
  VGA_COLOR_LIGHT_MAGENTA,
  VGA_COLOR_LIGHT_BROWN,
  VGA_COLOR_WHITE
} vga_color_t;

size_t terminal_row;
size_t terminal_col;
uint8_t terminal_color;
uint16_t * terminal_buffer;

void terminal_setcolor(uint8_t);
size_t kstrlen(const char *);
void terminal_putat(char, uint8_t, size_t, size_t);
void terminal_putchar(char);
void terminal_write(const char *, size_t);
void terminal_writestr(const char *);
void kinit(void);

static inline uint8_t vga_entry_color(vga_color_t fg, vga_color_t bg)
{
  return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
  return (uint16_t) uc | (uint16_t) color << 8;
}

void terminal_setcolor(uint8_t color)
{
  terminal_color = color;
}

size_t kstrlen(const char * str)
{
  size_t len;

  len = 0;

  while (str[len] != '\0')
    len++;

  return len;
}

void terminal_putat(char c, uint8_t color, size_t x, size_t y)
{
  size_t index;

  index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
  if (c != '\n')
  {
    terminal_putat(c, terminal_color, terminal_col, terminal_row);
    terminal_col++;
  }
  else
  {
    terminal_col = VGA_WIDTH;
  }

  if (terminal_col == VGA_WIDTH)
  {
    terminal_col = 0;
    terminal_row++;
    if (terminal_row == VGA_HIGHT)
      terminal_row = 0;
  }
}

void terminal_write(const char * data, size_t size)
{
  size_t i;

  for (i = 0; i < size; i++)
    terminal_putchar(data[i]);
}

void terminal_writestr(const char * str)
{
  size_t len;

  len = kstrlen(str);

  terminal_write(str, len);
}

void kinit(void)
{
  size_t x, y, index;

  terminal_row = 0;
  terminal_col = 0;
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = (uint16_t *) 0xb8000;

  for (y = 0; y < VGA_HIGHT; y++)
  {
    for (x = 0; x < VGA_WIDTH; x++)
    {
      index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void kmain(void)
{
  // initialize the terminal interface
  kinit();

  terminal_writestr("Welcome to Newbix");
}
