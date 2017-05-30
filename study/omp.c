#include <stdio.h>

int main(void) {

	int i = 0;
	#pragma omp parallel for num_threads(4)
	for(i = 'A';i <= 'Z';i++) {
			printf("%c\n",i);
	}

	return 0;
}
