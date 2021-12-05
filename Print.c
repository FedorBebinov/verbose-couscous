//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define max_dim 10
extern int size_obj;
extern char buf[];

void print(FILE* output_file) {
	int len = *((int*)(buf + 4));
	char* tmp = buf + 16;
	char* tmp1;
	for (int i = 0; i < len; ++i) {
		tmp1 = tmp + size_obj;
		int type = *((int*)tmp);
		int dim = *((int*)(tmp + 4));
		tmp = tmp + 16;
		if (type == 0 || type == 1) {
			int iter = 0;
			while (iter < dim * dim) {
				for (int i = 0; i < dim; ++i) {
					fprintf(output_file, "%.2lf ", *(double*)tmp);
					++iter;
					tmp = tmp + 8;
				}
				fprintf(output_file, "\n");
			}
			fprintf(output_file, "\n");
		}
		else if (type == 2) {
			for (int i = 0; i < dim; ++i) {
				for (int j = 0; j < dim; ++j) {
					fprintf(output_file, "%.2lf ", *(double*)tmp);
					tmp = tmp + 8;
				}
				fprintf(output_file, "\n");
			}
			fprintf(output_file, "\n");
		}
		tmp = tmp1;
	}
}
