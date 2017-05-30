#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void setup_sigs();

int main();

void exit_handler(int dummy) {
		int p_id = fork();

		if(p_id < 0) {
				printf("Error forking\n");
				exit(1);
		} else  {
				main();
				printf("%d\n",getpid());
		} 
}

void setup_sigs() {
		signal(SIGINT, exit_handler);
		signal(SIGTERM, exit_handler);
		signal(SIGABRT, exit_handler);
		signal(SIGCHLD, exit_handler);
}

int main(void) {
		setup_sigs();

		while(1);
}


