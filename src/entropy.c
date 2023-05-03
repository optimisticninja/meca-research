#include "entropy.h"

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#define BITS(t) (sizeof(t) * CHAR_BIT)

// Computes the entropy of a uint64_t value
double shannon_entropy(uint64_t value)
{
	int counts[256];
	memset(counts, 0, sizeof(counts));

	// Count the occurrence of each byte value
	uint8_t* bytes = (uint8_t*) &value;
	for (size_t i = 0; i < sizeof(value); i++) {
		counts[bytes[i]]++;
	}

	// Compute the entropy using the counts
	double entropy = 0.0;
	for (int i = 0; i < 256; i++) {
		if (counts[i] > 0) {
			double p = (double) counts[i] / sizeof(value);
			entropy -= p * log2(p);
		}
	}

	return entropy;
}


// Estimates the Kolmogorov complexity of a uint64_t by compressing it using zlib
double kolmogorov_entropy(uint64_t n) {
	uint64_t mask = 0x1;
	int count = 0;
	double entropy = 0.0;

	while (n > 0) {
		if (n & mask) {
			count++;
		} else {
			if (count > 0) {
				entropy += ((double) count / 64.0) * log2((double) count / 64.0);
				count = 0;
			}
		}
		n >>= 1;
	}

	if (count > 0) {
		entropy += ((double) count / 64.0) * log2((double) count / 64.0);
	}

	return -entropy;
}

// Tests if the given 64-bit values pass the bit-avalanche test
bool bit_avalanche_test(uint64_t state1, uint64_t state2)
{
	uint64_t diff = state1 ^ state2;
	// TODO: Fix warning on mask
	uint64_t mask = ((uint64_t) 1 << BITS(state1)) - 1;
	uint64_t inv_mask = ~mask;

	// Count the number of bits that differ between the two states
	uint64_t count = 0;
	while (diff != 0) {
		count++;
		diff &= (diff - 1);
	}

	// The proportion of bits that differ should be approximately 50%
	uint64_t expected = mask >> 1;
	return count >= (expected - (expected >> 4)) && count <= (expected + (expected >> 4));
}
