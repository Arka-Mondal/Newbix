/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2023  Arka Mondal
*/

ENTRY (_start)

SECTIONS
{
  . = 1M;

  .text BLOCK(4K) : ALIGN(4K)
  {
    *(.multiboot)
    *(.text)
  }

  .rodata BLOCK(4K) : ALIGN(4K)
  {
    *(.rodata)
  }

  .data BLOCK(4K) : ALIGN(4K)
  {
    *(.data)
  }

  .bss BLOCK(4K) : ALIGN(4K)
  {
    *(COMMON)
    *(.bss)
  }
}
