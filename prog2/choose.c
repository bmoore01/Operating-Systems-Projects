#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

long double fac(int n) {
		if(n == 1)
				return n;
		else
				return n * fac(n-1);
}


int main(int argc, char **argv[]) {
		if(argc != 3) {
				printf("Usage: choose  <from> <number>\n");
				exit(EXIT_FAILURE);
		}

		int m = atoi(argv[1]);
		int n = atoi(argv[2]);
		long double nfac;
		int pfds[2]; // input and output of pipe respectively
		long int result;

		pipe(pfds);	// create the pipe
		int pid = fork();

		if(pid < 0) {
				printf("Fork failed\n");
				exit(EXIT_FAILURE);
		}
		else if(pid == 0) {
				nfac = fac(n); // calculate n!
				// pass result to pipe
				write(pfds[1],&nfac,sizeof(nfac)); 
		}
		else {
				wait(NULL);
				long double result;
				long double mfac = fac(m);
				long double combi = fac(m-n);
				long double first = mfac / combi;


				// read from pipe into nfac
				read(pfds[0],&nfac,sizeof(nfac));
				long double second = mfac / nfac;
				result = first + second;
				printf("The result is %ld\n",result);
		}

		return 0;
}

