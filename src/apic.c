/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2024  Arka Mondal
*/

#include "apic.h"
#include "stdio.h"

uint8_t lapic_ids[MAX_NCORES];
uint8_t ncores;
uint64_t lapic_ptr;
uint32_t ioapic_ptr;

void detect_cores(uint8_t * apic_addr)
{
  uint8_t * end_ptr, * ptr;

  ptr = apic_addr;

  // lapic_ptr = (uint32_t) *((uint32_t * ) (apic_addr + 36));
  lapic_ptr = ((apic_t *) (apic_addr))->lapic_addr;
  // end_ptr = ptr + *((uint32_t * ) (apic_addr + 4));
  end_ptr = ptr + ((apic_t *) (apic_addr))->length;

  for (ptr = ((apic_t *) (apic_addr))->intr_controller_struct;
       ptr < end_ptr; ptr += ptr[1])
  {
    switch (ptr[0])
    {
      case 0:
        if (ptr[4] & 0x1)
        {
          lapic_ids[ncores] = ptr[3];
          ncores++;
        }
        break;

      case 1:
        ioapic_ptr = *((uint32_t *) (ptr + 4));
        break;

      case 5:
        lapic_ptr = *((uint64_t *) (ptr + 4));
        break;

      default:
        break;
    }
  }

  printf("Found %d cores, IOAPIC: %x, LAPIC: %x\n", ncores, ioapic_ptr, lapic_ptr);
}
