#pragma once

#include <stdbool.h>
#include <stdint.h>

double shannon_entropy(uint64_t);
double kolmogorov_entropy(uint64_t);
bool bit_avalanche_test(uint64_t, uint64_t);

