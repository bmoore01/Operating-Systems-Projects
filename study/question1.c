#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#define SIZE 1024
#define READ 0
#define WRITE 1

int main(void) {
	int fd[2];
	pid_t pid;

	int sum = 0;
	int product = 1;

	if(pipe(fd) == -1) {
			printf("Pipe failed\n");
			exit(EXIT_FAILURE);
	}

	pid = fork();

	if(pid < 0) {
			printf("Fork failed\n");
			exit(EXIT_FAILURE);
	} else if(pid > 0) { // is parent
		int i;
		for(i = 1; i < 10;i++)  
				product *= i;

		wait(NULL);

		close(fd[WRITE]);
		read(fd[READ], &sum,sizeof(int));
		close(fd[READ]);

		printf("The product is calculated in the child as %d\n",product);
		printf("The sum is calculated in the child as %d\n",sum);
	} else {
			int j;
			for(j = 0;j < 10;j++)
					sum += j;
			close(fd[READ]);
			write(fd[WRITE],&sum,sizeof(int));
			close(fd[WRITE]);
	}

	return 0;
}
