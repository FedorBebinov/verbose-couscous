extern int size_obj;
extern char buf[];

void delElem() {
	int k_obj = *((int*)(buf + 4));
	double total_aver = *((double*)(buf + 8));
	char* tmp = buf + 16;
	char* tmp1=tmp;
	for (int i = 0; i < k_obj; ++i) {
		tmp1 += size_obj;
		double aver = *((double*)(tmp + 8));
		if (aver + 0.000001 < total_aver) {
			*((int*)tmp) = -1;
		}
		tmp = tmp1;
	}
}