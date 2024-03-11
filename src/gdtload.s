# gdtload.s : load the gdt
# Licensed under GPLv3
# Author    : Arka Mondal
# Date      : 18th May, 2023
# Copyright (C) 2024  Arka Mondal

.text
.global load_gdt
.type load_gdt, @function
load_gdt:
  pushl     %ebp
  movl      %esp, %ebp

  movl      8(%ebp), %eax
  lgdt      (%eax)

  # loading code segment
  movl      12(%ebp), %eax
  pushl     %eax
  pushl     $reload_cs
  retf
reload_cs:

  # loading data segment
  movl      16(%ebp), %eax
  movw      %ax, %ss
  movw      %ax, %ds
  movw      %ax, %es
  movw      %ax, %fs
  movw      %ax, %gs

  movl      %ebp, %esp
  popl      %ebp
  ret
