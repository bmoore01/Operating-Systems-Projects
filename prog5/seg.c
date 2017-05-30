#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

void usage(char *name) {
		printf("Usage: %s <pid>\n",name);
}

int main(int argc, char** argv[]) {
		if(argc != 2)
				usage(argv[0]);
		pid_t pid = atoi(argv[1]);
		kill(pid, SIGSEGV);
		return 0;
}
