#include <stdio.h>


int main(void) {
		int i;
		int *p;

		p = &i;

		i = 10;

		printf("i is %d\n",i);
		printf("*p is %d\n",*p);
		printf("p is %p\n",p);

		*p = 15;

		printf("i is now %d\n",i);
		printf("*p  is now %d\n",*p);
		printf("p is now %p\n",p);

		return 0;
}
