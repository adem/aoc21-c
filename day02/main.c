#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// "forward" is the longest expected string.
#define MAX_STRLEN 7

int solve_1(char *filename) {
	FILE *f = fopen(filename, "r");
	int hpos = 0;
	int depth = 0;
	char *direction = malloc((MAX_STRLEN + 1) * sizeof(char));
	int units;
	while (!feof(f)) {
		fscanf(f, "%s %d\n", direction, &units);
		switch (direction[0]) {
			case 'f': // Forward
				hpos += units;
				break;
			case 'd': // Down
				depth += units;
				break;
			case 'u': // Up
				depth -= units;
				break;
		}
	}
	free(direction);
	fclose(f);
	return hpos * depth;
}

int solve_2(char *filename) {
	FILE *f = fopen(filename, "r");
	int hpos = 0;
	int aim = 0;
	int depth = 0;
	char *direction = malloc(MAX_STRLEN * sizeof(char));
	int units;
	while (!feof(f)) {
		fscanf(f, "%s %d\n", direction, &units);
		switch (direction[0]) {
			case 'f': // Forward
				hpos += units;
				depth += aim * units;
				break;
			case 'd': // Down
				aim += units;
				break;
			case 'u': // Up
				aim -= units;
				break;
		}

	}
	free(direction);
	fclose(f);
	return hpos * depth;
}

int main(void) {
	assert(solve_1("test.txt") == 150);
	printf("%d\n", solve_1("input.txt"));
	assert(solve_2("test.txt") == 900);
	printf("%d\n", solve_2("input.txt"));
}
