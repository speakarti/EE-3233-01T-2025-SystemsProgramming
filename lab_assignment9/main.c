#include <stdio.h>
#include "nop_slide.h"

int main()
{
  unsigned cycles = nop_slide();

  printf("Time-Stamp Counter cycles from nop_slide = %u\n", cycles);
}

