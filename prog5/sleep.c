#include <stdio.h>
#include <signal.h>

void alarm_handler() {
		return;
}

void sleep(int seconds) {
		signal(SIGALRM, alarm_handler);
		alarm(seconds);
		pause();
}

int main() {
		printf("Should sleep for five seconds\n");
		sleep(5);
		printf("It worked!\n");
		return 0;
}

