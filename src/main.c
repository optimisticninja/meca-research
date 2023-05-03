/**
 * TODO: Find highest entropy rules within X number of steps
 * TODO: Pass rule to encrypt/decrypt function
 * TODO: Dynamically select rule
 * TODO: Dynamically set number of epochs (with ceiling for lower compute time)
 * TODO: Pass array of words to encrypt/decrypt and iterate over multiple words as sequential timesteps
 */

#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#include "entropy.h"

#define BITS(t)	(sizeof(t) * CHAR_BIT)
#define HIGHEST_BIT(t) (BITS(t) - 1)

static const uint64_t CYCLIC64 = 0b0100110001110000111100000111110000001111110000000111111100000000;

// Prints a binary representation of the given number
void printbin(uint64_t n)
{
	for (int i = sizeof(uint64_t) * CHAR_BIT - 1; i >= 0; i--)
		printf("%lu", (n >> i) & 1);
}

// Computes the next state of the automata using the given transition table
uint64_t next_state(uint64_t state, const uint8_t* table)
{
	uint64_t next = 0;
	const int nhs = 3;
	const int reach = nhs >> 1;

	for (size_t i = 0; i < BITS(state); i++) {
		uint8_t neighborhood = 0;

		// Build neighborhood by bitwise shifting and masking
		for (int displacement = i - reach, index = 0; displacement <= (int) i + reach; displacement++, index++) {
			uint64_t masked_displacement = displacement & (BITS(state) - 1);
			neighborhood |= (state >> masked_displacement) & 0x01;
			neighborhood <<= 1;
		}
		neighborhood >>= 1; // remove last shift

		// Compute next state using transition table and neighborhood
		next |= table[neighborhood] << i;
	}

	printf("%f - %s\n", entropy(next), bit_avalanche_test(state, next) ? "true" : "false");
	return next;
}

// Runs the automata forward for the given number of steps
void encrypt(uint64_t state, const uint8_t* table, int num_steps)
{
	//printf("Initial state: ");
	//printbin(state);
	//printf("\n");

	for (int i = 0; i < num_steps; i++) {
		state = next_state(state, table);
		//printf("Step %d: ", i + 1);
		//printbin(state);
		//printf("\n");
	}
}

// Runs the automata backward for the given number of steps
void decrypt(uint64_t state, const uint8_t* table, int num_steps)
{
	//printf("Final state: ");
	//printbin(state);
	//printf("\n");

	for (int i = 0; i < num_steps; i++) {
		state = next_state(state, table);
		//printf("Step %d: ", num_steps - i);
		//printbin(state);
		//printf("\n");
	}
}

int main()
{
	// Run the automata forward and backward for 30 steps each for all 256 rules
	for (uint32_t rule = 0; rule < UINT32_MAX; rule++) {
		uint8_t transition_table[32];
		for (int i = 0; i < 32; i++) {
			transition_table[i] = (rule >> i) & 0x01;
		}

		//printf("\nRule %d:\n", rule);
		encrypt(CYCLIC64, transition_table, 30);
		//printf("\n");
		decrypt(CYCLIC64, transition_table, 30);
	}

	return 0;
}
