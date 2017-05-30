#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
		
		// check there is the correct amount of arguments
		if(argc != 3) {
				printf("Usage: copy origianl copyFile\n");
				exit(EXIT_FAILURE);
		}

		// vaiable declarations
		FILE *original = fopen(argv[1], "r");	
		FILE *copyFile = fopen(argv[2], "w");
		char temp;

		// copy file
		printf("copying [");
		while((temp  = fgetc(original)) != EOF) {
				fputc(temp, copyFile);
				printf("#");
		}

		printf("]\n");

		// close open files
		fclose(original);
		fclose(copyFile);

		// program successful
		return 0;
}
