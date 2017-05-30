#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#define SIZE 4096


int main(int argc, const char *argv[]) {

		int shm_fd;
		void *shm_ptr;

		if(argc > 3) {
				printf("usage: %s [PAWSID]\n",argv[0]);
				exit(EXIT_FAILURE);
		} else if (argc == 2) {

			const char *name = argv[1];

			shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
			shm_ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

			printf("Read from %s:\n%s\n",name,(char *)shm_ptr);
			shm_unlink(name);
		} else {
				const char *name = "bmoor64";
				const char *message = "Hello!";

				shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
				ftruncate(shm_fd, SIZE);
				shm_ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

				char msg[256];
				fgets(msg,sizeof(msg),stdin);

				sprintf(shm_ptr, "%s", msg);
				sscanf(shm_ptr, "%s",msg);
				printf("Written to %s\n",name);
		}

		return 0;
}

		
