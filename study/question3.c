#include <stdio.h>

int main(void) {

	int i;
	int sum = 0;
	#pragma omp parallel shared(sum)

	#pragma omp for reduction(+:sum)
	for(i = 0;i <= 30;i++) {
			printf("%d\n",i);
			sum += i;
	}

	printf("The result of sum is %d\n",sum);

	return 0;
}

		
