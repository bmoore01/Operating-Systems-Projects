#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#define SIZE 4096

int main() {
		const char *name = "46roomb";
		const char *message = {0x55, 0x48, 0x89, 0xe5, 0x89, 0x7d, 0xfc, 0x83, 0x45, 0xfc, 0x01, 0x8b, 0x45, 0xfc, 0x8d, 0x50, 0x01, 0x89, 0x55, 0xfc, 0x5d, 0xc3, '\0'};

	int shm_fd;
	void *shm_ptr;
	
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0777);
	ftruncate(shm_fd, SIZE);	
	shm_ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	sprintf(shm_ptr, "%s", message);
	char buffer[256];
	sscanf(shm_ptr, "%s", buffer);
	printf("Written: %s", message);

	return 0;
}
