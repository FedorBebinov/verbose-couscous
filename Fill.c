//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max_dim 10
extern int min_rnd;
extern int size_obj;
extern char buf[];
void fill_rnd(char* tmp);
void fill_obj(FILE* input_file, char* tmp);

void fill(FILE* input_file) {
	int k_obj = *((int*)(buf + 4));
	char* tmp = buf + 16;
	for (int i = 0; i < k_obj; ++i) {
		if (k_obj >= min_rnd) {
			int type = rand() % 3;
			int dim = rand() % max_dim + 1;
			*((int*)tmp) = type;
			*((int*)(tmp + 4)) = dim;
			fill_rnd(tmp);
		}
		else {
			int type;
			if (fscanf(input_file, "%d", &type) != 1) {
				printf("Invalid type of Matrix");
			}
			else {
				int dim;
				if (fscanf(input_file, "%d", &dim) != 1) {
					printf("Incorrect format of dimension");
				}
				else {
					*((int*)tmp) = type;
					*((int*)(tmp + 4)) = dim;
					fill_obj(input_file, tmp);
				}
			}
		}
		tmp = tmp + size_obj;
	}
}
void fill_rnd(char* tmp) {
	int type = *((int*)tmp);
	int dim = *((int*)(tmp + 4));
	*((double*)(tmp+8)) = 0.;
	tmp = tmp + 16;
	if (type == 0) {
		for (int i = 0; i < dim * dim; ++i) {
			if (i % dim == i / dim) {
				*((double*)tmp) = (double)(rand() % 1000);
			}
			else {
				*((double*)tmp) = 0.;
			}
			tmp = tmp + 8;
		}
	}
	else if (type == 1) {
		for (int i = 0; i < dim * dim; ++i) {
			if (i % dim <= i / dim) {
				*((double*)tmp) = (double)(rand() % 1000);
			}
			else {
				*((double*)tmp) = 0.;
			}
			tmp = tmp + 8;
		}
	}
	else {
		for (int i = 0; i < dim; ++i) {
			for (int j = 0; j < dim; ++j) {
				*((double*)tmp) = (double)(rand() % 1000);
				tmp = tmp + 8;
			}
		}
	}
}
void fill_obj(FILE* input_file, char* tmp) {
	int type = *((int*)tmp);
	int dim = *((int*)(tmp + 4));
	*((double*)(tmp + 8)) = 0.;
	tmp = tmp + 16;
	if (type == 0) {
		for (int i = 0; i < dim * dim; ++i) {
			if (i % dim == i / dim) {
				if (fscanf(input_file, "%lf", (double*)tmp) != 1) {
					printf("Incorrect format");
					break;
				}
			}
			else {
				*((double*)tmp) = 0.;
			}
			tmp = tmp + 8;
		}
	}
	else if (type == 1) {
		for (int i = 0; i < dim * dim; ++i) {
			if (fscanf(input_file, "%lf", (double*)tmp) != 1) {
				printf("Incorrect format");
				break;
			}
			tmp = tmp + 8;
		}
	}
	else {
		for (int i = 0; i < dim; ++i) {
			for (int j = 0; j < dim; ++j) {
				if (fscanf(input_file, "%lf", (double*)tmp) != 1) {
					printf("Incorrect format");
					break;
				}
				tmp = tmp + 8;
			}
		}
	}
}

