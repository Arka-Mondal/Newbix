/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2024  Arka Mondal
*/

#include "idt.h"

idtentry_t kidt[256];
idtdesc_t kidtdesc = {.limit = sizeof(kidt) - 1, .address = kidt};

void idt_init(void)
{
  idt_load(&kidtdesc);
}

void idt_setgate(unsigned int intrno, void * offset,
                 uint16_t segselect, uint8_t flag)
{
  kidt[intrno].offsetlow = ((uint32_t) offset) & 0xffff;
  kidt[intrno].segselector = segselect;
  kidt[intrno].reserved = 0x0;
  kidt[intrno].flags = flag;
  kidt[intrno].offsethigh = (((uint32_t) offset) >> 16) & 0xffff;
}

void idt_enablegate(unsigned int intrno)
{
  IDT_FLAG_SET(kidt[intrno].flags, IDT_FLAG_PRESENT);
}

void idt_disablegate(unsigned int intrno)
{
  IDT_FLAG_UNSET(kidt[intrno].flags, IDT_FLAG_PRESENT);
}
