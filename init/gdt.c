/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2023  Arka Mondal
*/

#include "../include/gdt.h"

gdtentry_t kgdt[3] = {
  [0] = GDT_MAKE_ENTRY(0, 0, 0, 0),
  [1] = GDT_MAKE_ENTRY(0, 0xffffffff,
                       GDT_ACC_PRESENT | GDT_ACC_RING0 |
                       GDT_ACC_CODE_SEGMENT | GDT_ACC_CODE_READABLE,
                       GDT_FLG_32BIT | GDT_FLG_GRAN_4K),
  [2] = GDT_MAKE_ENTRY(0, 0xffffffff,
                       GDT_ACC_PRESENT | GDT_ACC_RING0 |
                       GDT_ACC_DATA_SEGMENT | GDT_ACC_DATA_DIR_NORMAL | GDT_ACC_DATA_WRITABLE,
                       GDT_FLG_32BIT | GDT_FLG_GRAN_4K)
};

gdtdesc_t kgdtdesc = {.limit = sizeof(kgdt) - 1, .address = kgdt};

void gdt_init(void)
{
  load_gdt(&kgdtdesc, GDT_CODE_SEGMENT, GDT_DATA_SEGMENT);
}
