# idtload.s : load the idt descriptor
# Licensed under GPLv3
# Author    : Arka Mondal
# Date      : 25th May, 2023
# Copyright (C) 2023  Arka Mondal

.text
.global idt_load
.type idt_load, @function
idt_load:
  pushl     %ebp
  movl      %esp, %ebp

  # load the idt descriptor
  movl      8(%ebp), %eax
  lidt      (%eax)

  movl      %ebp, %esp
  popl      %ebp
  ret
