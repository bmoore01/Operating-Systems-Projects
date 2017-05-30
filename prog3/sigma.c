#include <stdio.h>

int main(int argc, char **argv[]) {
		if(argc != 4) {
				printf("Usage: %s <start> <stop> <step>\n",argv[0]);
				return 1;
		}

		int start = atoi(argv[1]);
		int stop = atoi(argv[2]);
		int step = atoi(argv[3]);

		int sum     = 0;
		int product = 1;
		int i;

		#pragma omp parallel for reduction(+:sum)
		for(i = start;i <= stop;i += step) {
				sum += i;
		}

		#pragma omp parallel for reduction(*:product)
		for(i = start;i <= stop;i += step) {
				product *= i;
				//printf("%d\t%d\n", i, product);
		}

		printf("Sum is %d\n",sum);
		printf("Product is %d\n",product);

		return 0;
}

