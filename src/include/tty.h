/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2024  Arka Mondal
*/

#ifndef _NEWBIX_TTY_H
#define _NEWBIX_TTY_H

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

void tty_init(void);
void tty_setcolor(uint8_t);
void tty_putat(char, uint8_t, size_t, size_t);
void tty_putchar(char);
void tty_write(const char *, size_t);
void tty_writestr(const char *);

#endif
