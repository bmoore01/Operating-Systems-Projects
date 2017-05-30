#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#define SIZE 4096

int main(int argc, char** argv[]) {

		void *shm_ptr;
		int shm_fd;
		const char *name = "kitties";

		shm_fd = shm_open(name,O_RDONLY,0777);

		shm_ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED,shm_fd, 0);

		printf("The contents of kitties is %s\n",(char *)shm_ptr);

		shm_unlink(name);

		return 0;
}
