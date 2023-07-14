/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2023  Arka Mondal
*/

#ifndef _NEWBIX_ACPI_H
#define _NEWBIX_ACPI_H

#include <stdint.h>

#define MULTIBOOT_TAG_TYPE_END 0
#define MULTIBOOT_TAG_TYPE_ACPI_OLD 14
#define MULTIBOOT_TAG_TYPE_ACPI_NEW 15

typedef struct {
  uint32_t type;
  uint32_t size;
} multiboot_tag_t;

typedef struct {
  uint32_t type;
  uint32_t size;
  uint8_t rsdp[0];
} multiboot_tag_acpi_t;

typedef struct {
  char signature[8];
  uint8_t checksum;
  char OEMID[6];
  uint8_t revision;
  uint32_t rsdt_addr;

  // fields added since acpi version 2.0
  uint32_t length;
  uint64_t xsdt_addr;
  uint8_t extended_checksum;
  uint8_t reserved[3];
} __attribute__((packed)) rsdp_desc_t;

typedef struct {
  char signature[4];
  uint32_t length;
  uint8_t revision;
  uint8_t checksum;
  char OEMID[6];
  char OEM_table_ID[8];
  uint32_t OEM_revision;
  uint32_t creator_ID;
  uint32_t creator_revision;
} __attribute__((packed)) acpisdt_header_t;

typedef struct {
  acpisdt_header_t header;
  uint32_t ptr_to_other_sdt[0];
} rsdt_t;

uint32_t get_rsdt_address(uint32_t);
uint8_t * find_apic(uint32_t);

#endif
