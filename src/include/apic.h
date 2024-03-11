/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2024  Arka Mondal
*/

#ifndef _NEWBIX_APIC_H
#define _NEWBIX_APIC_H

#include <stdint.h>
#define MAX_NCORES 256

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
  uint32_t lapic_addr;
  uint32_t flags;
  uint8_t intr_controller_struct[0];
} __attribute__((packed)) apic_t;

void detect_cores(uint8_t *);

#endif
