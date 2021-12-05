//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define max_dim 10
#define max_obj 20
#define size_obj0  (2 + max_dim * max_dim) * 8

int min_rnd = 11;
char buf[16 + max_obj * size_obj0];
int size_obj = size_obj0;

extern void average1();
extern void delElem1();
extern void print1(FILE* output_file);

void fill(FILE* input_file);
void print(FILE* output_file);
void average();
void printInf(FILE* output_file);
void delElem();

int main(int argc, char* argv[]) {
	// Check if the number of arguments is correct.
	if (argc < 2) {
		printf("Cannot found input file\n");
		exit(1);
	}
	// Open file stream for reading.
	FILE* input_file = fopen(argv[1], "r");
	if (input_file == NULL) {
		printf("Cannot access input file\n");
		exit(1);
	}
	// Open file stream for writing.
	FILE* output_file;
	if (argc == 3)
		output_file = fopen(argv[2], "w");
	else
		output_file = fopen("output.txt", "w");
	if (output_file == NULL) {
		printf("Cannot access output file\n");
		exit(1);
	}
	// Number of the future objects.
	int k_obj;
	// Reading the number from the file.
	if (fscanf(input_file, "%d", &k_obj) != 1) {
		printf("Incorrect format");
	}
	else {
		// Initialising a Container.
		*((int*)buf) = 0;
		*((int*)(buf + 4)) = k_obj;
		*((double*)(buf + 8)) = 0.;

		srand(time(0));
		
		print1(output_file);
		fill(input_file);
		print(output_file);
		average1();
		printInf(output_file);
		delElem1();
		fprintf(output_file, "After removing lower than average elements:\n");
		print(output_file);
	}
	fclose(input_file);
	fclose(output_file);
	printf("Finish!\n");
	return 0;
}
