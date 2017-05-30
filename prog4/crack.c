#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <crypt.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM 4

pthread_mutex_t mutex;

void ith(char *password, int index, int n) {
  for (int i=1; i<=n; i++) {
    password[i-1] = (index % 26) + 'a';
    index /= 26;
  }
  password[n] = '\0';
}

void *crack() {
	  char target[16];
	  int fd  = open("hash.txt", 'r');
	  int num = read(fd, target, 16);
	  if (num) target[num-1] = 0;
	  else     exit(0);
	  close(fd);
  		int N=pow(26, 4);
  		int M=pow(26, 2);
		char *hash;
		char password [5];
		char salt[3];
		for(int i = 0; i < N;i++) {
				ith(password, i, 4);
				for(int j = 0;j < M;j++) {
						ith(salt, j ,2);
						// lock it here
						//while(pthread_mutex_trylock(&mutex));
						pthread_mutex_lock(&mutex);
						hash = crypt(password,salt);
						if(0==strcmp(hash, target)) {
        					printf("Password: %s\t\tSalt: %s\t\tHash: %s\t\tTarget: %s\n", password, salt, hash, target);
							exit(1);
							} else {
									printf("Trying %s..\r", password);	
									pthread_mutex_unlock(&mutex);
							}
				}
		}
}

int main() {
  char target[16];

  int fd  = open("hash.txt", 'r');
  int num = read(fd, target, 16);
  if (num) target[num-1] = 0;
  else     exit(0);
  close(fd);

  pthread_mutex_init(&mutex, NULL);

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_t tid[NUM];

  for(int i = 0;i < NUM;i++) {
    	pthread_create(&tid[i], &attr, crack, target);
  }

  for(int i = 0;i < NUM;i++)
		  pthread_join(tid[i],NULL);

}
