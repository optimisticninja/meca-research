#include "patterns.h"

#include <limits.h>
#include <stdlib.h>

uint64_t cyclic(int num_bits)
{
  uint64_t pattern = 0;
  for (int i = 0; i < num_bits; i++)
    pattern |= ((uint64_t) 1 << (num_bits - i - 1));
  pattern |= (pattern >> num_bits);
  return pattern;
}

uint64_t one()
{
  // Shift 1 to the middle bit index and OR it with the value
  return 0 | (1ULL << (63 / 2));
}

uint64_t ones() { return 0xFFFFFFFFFFFFFFFF; }

uint64_t randomu64()
{
  // Generate two 32-bit random numbers and combine them into a single 64-bit number
  uint64_t rand_hi = (uint64_t) rand() << 32;
  uint64_t rand_lo = (uint64_t) rand();
  return rand_hi | rand_lo;
}

uint64_t half()
{
  if (rand() % 2)
    return 0x00000000FFFFFFFF;
  else
    return 0xFFFFFFFF00000000;
}
