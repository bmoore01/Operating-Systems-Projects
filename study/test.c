#include<omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	  int th_id, nthreads;
	  char c = 'a';
	    #pragma omp parallel private(th_id)
	    {
				for(;c < 'z';c++) {
						printf("%c\n",c);
				}
		}
		  return EXIT_SUCCESS;
}
