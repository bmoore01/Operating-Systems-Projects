#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv[]) {
		if(argc != 2) {
				printf("Usage: echo <filename>\n");
				exit(EXIT_FAILURE);
		}

		int input = open("/dev/stdin", O_RDONLY);
		int stdo = open("/dev/stdout", O_WRONLY);
		int fileout = open(argv[1], O_WRONLY);

		char buf[1];

		while(read(input,buf,sizeof(char))) {
				write(stdo,buf,sizeof(char));
				write(fileout,buf,sizeof(char));
		}

		close(input);
		close(stdo);
		close(fileout);

		return 0;
}
