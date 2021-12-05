extern int size_obj;
extern char buf[];

void average() {
	int k_obj = *((int*)(buf + 4));
	char* tmp = buf + 16;
	char* tmp1;
	double sum = 0.;
	int len = 0;
	for (int i = 0; i < k_obj; ++i) {
		tmp1 = tmp + size_obj;
		int type = *((int*)tmp);
		int dim = *((int*)(tmp + 4));
		double* aver = (double*)(tmp + 8);
		tmp = tmp + 16;
		double sum_obj = 0.;
		int dim2 = dim * dim;
		for (int i = 0; i < dim2; ++i) {
			sum_obj = sum_obj + *((double*)tmp);
			tmp = tmp + 8;
		}
		*aver = sum_obj / dim2;
		len = len + dim2;
		sum = sum + sum_obj;
		tmp = tmp1;
	}
	//total average
	*((double*)(buf + 8)) = sum / len;
}
