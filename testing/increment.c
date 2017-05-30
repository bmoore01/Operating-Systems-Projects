#include <stdio.h>

void increment(int *p) {
		*p = *p + 1;
}

int main(void) {
		int i = 10;
		printf("i is %d\n",i);
		int *p = &i;

		//increment(&i);
		increment(p);
		
		printf("i is now %d\n",i);

		return 0;
}
