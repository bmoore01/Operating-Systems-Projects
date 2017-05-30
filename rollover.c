#include <stdio.h>
#include <unistd.h>

int main() {
		int last = 0;
		int curr = 0;

		int i;
		for(i = 0;;i++) {
				last = curr;
				curr = i;
				if(last > curr) {
						printf("The rollover limit is %d\n",last);
						printf("The next number is %d\n",curr);
						exit(0);
				}
		}

		return 0;
}
