#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_BITS 12

/*
 * Return a bit dominance array of size NUMBER_OF_BITS. The bit dominance array
 * represents which bit dominates per column. If the number in a given column is
 * greater than 0, 1 dominates. If the number is less than 0, 0 dominates.
 */
int *get_bit_dominance(char *filename) {
	FILE* f = fopen(filename, "r");
	int *bit_dominance = calloc(NUMBER_OF_BITS, sizeof(int));
	char *line = malloc((NUMBER_OF_BITS + 1) * sizeof(char));
	while (!feof(f)) {
		fscanf(f, "%s\n", line);
		// Assumption: `line` contains exactly NUMBER_OF_BITS bits.
		for (size_t i = 0; i < NUMBER_OF_BITS; ++i) {
			switch (line[i] - 48) {
				case 0:
					bit_dominance[i]--;
					break;
				case 1:
					bit_dominance[i]++;
					break;
			}
		}
	}
	free(line);
	fclose(f);
	return bit_dominance;
}

unsigned int get_gamma_rate(char *filename) {
	int *bit_dominance = get_bit_dominance(filename);

	unsigned int gamma_rate = 0;
	// Set a 1 at the correct position whenever the 1 dominates.
	for (size_t i = 0; i < NUMBER_OF_BITS; ++i) {
		if (bit_dominance[i] > 0)  {
			gamma_rate |= 1 << (NUMBER_OF_BITS - i - 1);
		}
	}

	free(bit_dominance);
	return gamma_rate;
}

int solve_1(char *filename) {
	unsigned int gamma_rate = get_gamma_rate(filename);
	// Inverting all `gamma_rate` bits yields `delta_rate`. Only consider
	// the NUMBER_OF_BITS bits to the right.
	size_t discard = (sizeof(gamma_rate) * 8) - NUMBER_OF_BITS;
	unsigned int delta_rate = ~gamma_rate << discard >> discard;
	return gamma_rate * delta_rate;
}

int solve_2(char *filename) {
	unsigned int oxygen_generator_rating = 0;
	unsigned int co2_scrubber_rating = 0;
	return oxygen_generator_rating * co2_scrubber_rating;
}

int main(void) {
	assert(solve_1("test.txt") == 0b001001111100 * 0b110110000011);
	printf("%d\n", solve_1("input.txt"));
	assert(solve_2("test.txt") == 0b101001101100 * 0b001001011100);
	printf("%d\n", solve_2("input.txt"));
	return EXIT_SUCCESS;
}
