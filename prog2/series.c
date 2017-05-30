#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int recur_sum(int n) {
		if(n == 1)
				return n;
		else
			return n + recur_sum(n - 1);
}

int recur_prod(int n) {
		if(n == 1)
				return n;
		else
				return n * recur_prod(n - 1);
}

int main(int argc, char **argv[]) {
				// if wrong amount of args 
				if(argc != 2) { 
						printf("Usage: series <number>\n");
						exit(EXIT_FAILURE);
				}

				// Get n and convert it to an interger
				int n = atoi(argv[1]);
				int result;

				int p_id = fork(); // time to fork!

				if(p_id < 0) 
						printf("Errof forking\n");
				// if pid is parent
				else if(p_id > 0) {
						result = recur_prod(n);
						wait(NULL);
						printf("The parent process has calculated the product of all numbers up to %d as %d\n",n,result);
				//pid is child 
				} else { 
					result = recur_sum(n);
					printf("The child process has calculated the sum of all numbers up to %d as %d\n",n,result);
				}

				return 0;
}





