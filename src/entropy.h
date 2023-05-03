#pragma once

#include <stdbool.h>
#include <stdint.h>

double entropy(uint64_t);
bool bit_avalanche_test(uint64_t, uint64_t);
