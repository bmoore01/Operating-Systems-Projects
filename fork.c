#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
		pid_t pid = fork();
		pid_t cur;
		if (pid < 0) {
				printf("Fork failed\n");
		}
		else if (pid == 0) {
				printf("Child: %d\n", pid);
				cur = getpid();
				printf("My PID: %d\n", cur);
		}
		else if (pid > 0) {
				printf("Parent: %d\n", pid);
				cur = getpid();
				printf("My PID: %d\n", cur);
				wait(NULL);
		}
}
