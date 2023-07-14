/*
 * Licensed under GPLv3
 * Author    : Arka Mondal
 * Copyright (C) 2023  Arka Mondal
*/

#include "../include/string.h"

size_t strlen(const char * str)
{
  size_t len;

  len = 0;

  while (str[len] != '\0')
    len++;

  return len;
}

int strcmp(const char * str1, const char * str2)
{
  for (; *str1 == *str2; str1++, str2++)
  {
    if (*str1 == '\0')
      return 0;
  }

  return (*(const unsigned char *) str1 < *(const unsigned char *) str2) ? -1 : 1;
}

int strncmp(const char * str1, const char * str2, size_t n)
{
  for (; 0 < n; n--, str1++, str2++)
  {
    if (*str1 != *str2)
      return (*(const unsigned char *) str1 < *(const unsigned char *) str2) ? -1 : 1;
    else if (*str1 == '\0')
      break;
  }

  return 0;
}
