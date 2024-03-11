/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2024  Arka Mondal
*/

#ifndef NEWBIX_IDT_H
#define NEWBIX_IDT_H

#include <stdint.h>

typedef struct {
  uint16_t offsetlow;
  uint16_t segselector;
  uint8_t reserved;
  uint8_t flags;
  uint16_t offsethigh;
} __attribute__((packed)) idtentry_t;

typedef struct {
  uint16_t limit;
  idtentry_t * address;
} __attribute__((packed)) idtdesc_t;

typedef enum {
  IDT_FLAG_GATE_TASK          = 0x5,
  IDT_FLAG_GATE_16BIT_INTR    = 0x6,
  IDT_FLAG_GATE_16BIT_TRAP    = 0x7,
  IDT_FLAG_GATE_32BIT_INTR    = 0xe,
  IDT_FLAG_GATE_32BIT_TRAP    = 0xf,

  IDT_FLAG_RING0              = 0x00,       // (0 << 5)
  IDT_FLAG_RING1              = 0x20,       // (1 << 5)
  IDT_FLAG_RING2              = 0x40,       // (2 << 5)
  IDT_FLAG_RING3              = 0x60,       // (3 << 5)

  IDT_FLAG_PRESENT            = 0x80
} idtflag_t;

#define IDT_FLAG_SET(x, flag) ((x) |= (flag))
#define IDT_FLAG_UNSET(x, flag) ((x) &= ~(flag))

void idt_load(idtdesc_t *);
void idt_init(void);
void idt_setgate(unsigned int, void *, uint16_t, uint8_t);
void idt_enablegate(unsigned int);
void idt_disablegate(unsigned int);

#endif
