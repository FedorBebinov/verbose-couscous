//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
extern int size_obj;
extern char buf[];

void printInf(FILE* output_file) {
	int k_obj = *((int*)(buf + 4));
	char* tmp = buf + 16;
	for (int i = 0; i < k_obj; ++i) {
		int type = *((int*)tmp);
		int dim = *((int*)(tmp + 4));
		double aver = *((double*)(tmp + 8));
		fprintf(output_file, "element %i: type %i dimension %i average %.2lf \n", i + 1, type, dim, aver);
		tmp = tmp + size_obj;
	}
	fprintf(output_file, "total average %.2lf\n\n", *((double*)(buf + 8)));
}
