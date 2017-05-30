#include <stdio.h>
#include <pthread.h>

#define NUM 10000
#define THREADS 4

void *calcPi(void *param) {

		srand(time(NULL));
		int i, inside=0; 
		double x, y,result;
		double *vals = param;

		for (i=0; i<NUM; i++) {
				x = (rand()%NUM)/(double)NUM;
				y = (rand()%NUM)/(double)NUM;
				if (x*x + y*y < 1)
						inside++;
		}

		result = (double)(4.0*inside/(double)NUM);
		vals[0] = result;
}


int main() {
	int i;
	double results[THREADS][1] = {
			{0},
			{0},
			{0},
			{0}
	};
	double total, avg;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t tid[THREADS];

	for(i = 0;i < THREADS; i++)
			pthread_create(&tid[i],&attr,calcPi,results[i]);

	for(i = 0;i < THREADS;i++)
			pthread_join(tid[i],NULL);

	for(i = 0;i < THREADS;i++) {
			printf("Approximation %d: %.4f\n",i,results[i][0]);
			total += results[i][0];
	}
	
	avg = total / THREADS;
	printf("Average approximation is %.4f\n",avg);

	return 0;
}
