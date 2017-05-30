#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#define SIZE 4096

int main(void) {
		const char *name = "46roomb";

		int shm_fd;
		void *shm_ptr;

		shm_fd = shm_open(name, O_CREAT | O_RDWR, 0777);
		shm_ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

		//char bytecode[SIZE];

		//strcpy(bytecode,(char *)shm_ptr);

		printf("Read this bytecode: %s\n",(char *)shm_ptr);

		int n = 5;
		printf("n is equal to %d\n",n);

		int result;

		
		int (*fun_ptr)(int) = shm_ptr;
		result = (*fun_ptr)(n);

		printf("now n is equal to %d\n",result);
		shm_unlink(name);

		return 0;
}
