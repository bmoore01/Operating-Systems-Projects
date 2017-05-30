#include <stdio.h>

#define NUM 10000000

int main() {

		srand(time(NULL));
		int i, inside=0; 
		double x, y;

		for (i=0; i<NUM; i++) {
				x = (rand()%NUM)/(double)NUM;
				y = (rand()%NUM)/(double)NUM;
		        //printf("%.2f %.2f\n", x, y);
				if (x*x + y*y < 1)
						inside++;
		        //printf("inside: %d\n", inside);
		}

		printf("%.4f\n", (double)(4.0*inside/(double)NUM));

}
