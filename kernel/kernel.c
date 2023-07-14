/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2023  Arka Mondal
*/

#include "../include/acpi.h"
#include "../include/apic.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/stdio.h"
#include "../include/tty.h"

void kinit(void)
{
  gdt_init();
  idt_init();
  tty_init();
}

void kmain(uint32_t magicnum, uint32_t addr)
{
  uint32_t rsdtaddr;
  uint8_t * apicaddr;

  kinit();
  printf("EAX: 0x%x EBX: %d\n", magicnum, addr);

  if (magicnum != 0x36d76289)
  {
    printf("Something went wrong.\n");
    return;
  }

  printf("%d %d %d\n", sizeof(char), sizeof(long), sizeof(long long));
  rsdtaddr = get_rsdt_address(addr);
  apicaddr = find_apic(rsdtaddr);
  printf("0x%p\n", apicaddr);
  detect_cores(apicaddr);

  printf("Welcome to Newbix\n");
}
