#include <stdio.h>

#define N 50

int fac(int x) {
		if(x == 1)
				return x;
		else
				return x * fac(x-1);
}

int main() {
		int i = 1;
		int result;
		long double sum;

#pragma omp parallel for reduction(fac)
		for(;i < N;i++) {
			result = fac(i);
			sum += (long double)1/result;	
		}
		printf("%E\n", sum);
}
