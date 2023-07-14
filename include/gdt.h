/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2023  Arka Mondal
*/

#ifndef NEWBIX_GDT_H
#define NEWBIX_GDT_H

#include <stdint.h>
#define GDT_CODE_SEGMENT 0x8
#define GDT_DATA_SEGMENT 0x10

typedef struct {
  uint16_t seglimitlow;       // limit (bits 0-15)
  uint16_t baseaddrlow;       // base (bits 0-15)
  uint8_t baseaddrmid;        // base (bits 16-25)
  uint8_t accessmode;         // access
  uint8_t flaglimithigh;      // limit (bits 16-19) | flags
  uint8_t baseaddrhigh;       // base (bits 24-31)
} __attribute__((packed)) gdtentry_t;

typedef struct {
  uint16_t limit;             // sizeof(gdt_t) - 1
  gdtentry_t * address;       // base address of the gdt
} __attribute__((packed)) gdtdesc_t;

typedef enum {
  GDT_ACC_CODE_READABLE         = 0x02,
  GDT_ACC_DATA_WRITABLE         = 0x02,

  GDT_ACC_CODE_CONFORMING       = 0x04,
  GDT_ACC_DATA_DIR_NORMAL       = 0x00,
  GDT_ACC_DATA_DIR_DOWN         = 0x04,

  GDT_ACC_CODE_SEGMENT          = 0x18,
  GDT_ACC_DATA_SEGMENT          = 0x10,
  GDT_ACC_DESC_TASKSS           = 0x00,

  GDT_ACC_RING0                 = 0x00,
  GDT_ACC_RING1                 = 0x20,
  GDT_ACC_RING2                 = 0x40,
  GDT_ACC_RING3                 = 0x60,

  GDT_ACC_PRESENT               = 0x80,
} gdtaccess_t;

typedef enum {
  GDT_FLG_64BIT                 = 0x20,
  GDT_FLG_32BIT                 = 0x40,
  GDT_FLG_16BIT                 = 0x00,

  GDT_FLG_GRAN_1B               = 0x00,
  GDT_FLG_GRAN_4K               = 0x80
} gdtflag_t;

#define GDT_LIMIT_LOW(limit)                      ((limit) & 0xffff)
#define GDT_BASE_LOW(base)                        ((base) & 0xffff)
#define GDT_BASE_MID(base)                        (((base) >> 16) & 0xff)
#define GDT_FLAGS_LIMIT_HIGH(flags, limit)        ((((limit) >> 16) & 0xf) | ((flags) & 0xf0))
#define GDT_BASE_HIGH(base)                       (((base) >> 24) & 0xff)

#define GDT_MAKE_ENTRY(base, limit, access, flags)        \
{                                                         \
  .seglimitlow = GDT_LIMIT_LOW(limit),                    \
  .baseaddrlow = GDT_BASE_LOW(base),                      \
  .baseaddrmid = GDT_BASE_MID(base),                      \
  .accessmode = access,                                   \
  .flaglimithigh = GDT_FLAGS_LIMIT_HIGH(flags, limit),    \
  .baseaddrhigh = GDT_BASE_HIGH(base)                     \
}

void load_gdt(gdtdesc_t *, uint16_t, uint16_t);
void gdt_init(void);

#endif
