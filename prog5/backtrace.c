#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <execinfo.h>

void print_trace() {
		void *array[10];
		size_t size;
		char **strings;
		size_t i;
		size = backtrace(array, 10);
		strings = backtrace_symbols(array, size);
		printf("Obtained %zd stack frames.\n", size);
		for(i = 0;i < size;i++)
				printf("%s\n", strings[i]);
		free(strings);
}

void usage(char *name) {
		printf("Usage: %s <pid>\n",name);
}

int main(int argc, char **argv[]) {
		// Call signal(2)
		if(argc != 2)
				usage(argv[0]);
		pid_t pid = atoi(argv[1]);
		signal(SIGSEGV,print_trace);
		return 0;
}

