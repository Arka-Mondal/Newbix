/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2023  Arka Mondal
*/

#include "../include/acpi.h"
#include "../include/stdio.h"
#include "../include/string.h"

uint32_t get_rsdt_address(uint32_t address)
{
  uint8_t * baseaddr;
  multiboot_tag_t * tag;

  for (tag = (multiboot_tag_t *) (address + 8);
       tag->type != MULTIBOOT_TAG_TYPE_END;
       tag = (multiboot_tag_t *) ((uint8_t *) tag
                                      + ((tag->size + 7) & ~7)))
  {
    switch (tag->type)
    {
      case MULTIBOOT_TAG_TYPE_ACPI_OLD:
      case MULTIBOOT_TAG_TYPE_ACPI_NEW:
        baseaddr = ((multiboot_tag_acpi_t *) tag)->rsdp;
        if (strncmp(((acpisdt_header_t *) baseaddr)->signature, "RSD PTR", 7) != 0)
          return 0;

        return ((rsdp_desc_t *) baseaddr)->rsdt_addr;

        break;

      default:
        break;
    }
  }

  return 0;
}

uint8_t * find_apic(uint32_t root_sdt)
{
  int nentries, i;
  acpisdt_header_t * haddr;
  rsdt_t * rsdt_addr;

  rsdt_addr = (rsdt_t *) root_sdt;
  nentries = (rsdt_addr->header.length - sizeof(rsdt_addr->header)) / 4;

  for (i = 0;  i < nentries; i++)
  {
    haddr = (acpisdt_header_t *) rsdt_addr->ptr_to_other_sdt[i];
    if (!strncmp(haddr->signature, "APIC", 4))
    {
      // printf("APIC\n");
      return (uint8_t *) haddr;
    }
  }

  return NULL;
}
