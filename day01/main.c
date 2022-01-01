#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int solve_1(char *filename) {
	FILE* f = fopen(filename, "r");
	int increased = 0;
	int prev;
	int curr;
	fscanf(f, "%d\n", &prev);
	while (!feof(f)) {
		fscanf(f, "%d\n", &curr);
		if (prev < curr) {
			increased++;
		}
		prev = curr;
	}
	fclose(f);
	return increased;
}

int solve_2(char *filename) {
	FILE* f = fopen(filename, "r");
	int increased = 0;
	int first, second, third, fourth;
	fscanf(f, "%d\n%d\n%d\n", &first, &second, &third);
	while (!feof(f)) {
		fscanf(f, "%d\n", &fourth);
		if (first + second + third < second + third + fourth) {
			increased++;
		}
		first = second;
		second = third;
		third = fourth;
	}
	fclose(f);
	return increased;
}

int main(void) {
	assert(solve_1("test.txt") == 7);
	printf("%d\n", solve_1("input.txt"));
	assert(solve_2("test.txt") == 5);
	printf("%d\n", solve_2("input.txt"));

	return EXIT_SUCCESS;
}
