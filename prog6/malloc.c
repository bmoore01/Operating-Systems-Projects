#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

// typedef a boolean
typedef enum {false, true} bool;

// memory block info
struct mem_block {
		size_t size;
		struct mem_seg* next;
		bool free;
};
		
void* list_head = NULL;

#define BLOCK_SIZE sizeof(struct mem_block)

struct mem_block* find_free_mem_block(struct mem_block **last, size_t size) {
		struct mem_block *cur = list_head;
		while(cur && (!cur->free && !(cur->size >= size))) {
				*last = cur;
				cur = cur->next;
		}
		return cur;
}

struct mem_block* request_memspace_pls(struct mem_block* last, size_t size) {
		struct mem_block *new_block;
		new_block = sbrk(0);
		void *req = sbrk(size + BLOCK_SIZE);
		if((void*)new_block != req) 
				exit(EXIT_FAILURE);
		if(req == (void*) -1) // sbrk error
				return NULL;

		if(last) 
				last->next = new_block;

		new_block->size = size;
		new_block->next = NULL;
		new_block->free = false;
		return new_block;
}

void* malloc(size_t size) {
		struct mem_block *block;

		if(size <= 0) // if no size passed allocate no memory
				return NULL;

		if(!list_head) { // initial call
				block = request_memspace_pls(NULL, size);
				if(!block) 
						return NULL;

				list_head = block;
		} else {
				struct mem_block* last = list_head;
				block = find_free_mem_block(&last, size);
				if(!block) { // can't find a free block
						block = request_memspace_pls(last, size);
						if(!block)
								return NULL;
				} else { // free block found
						block->free = false;
				}
		}
		return(block + 1);
}


struct mem_block* pls_get_block_ptr(void *ptr) {
		return (struct mem_block*)ptr - 1;
}

void free(void* ptr) {
		if(!ptr) { // if no valid pointer, exit function
				return;
		}

		struct mem_block* mem_block_ptr = pls_get_block_ptr(ptr);
		if(mem_block_ptr != 0)
				exit(EXIT_FAILURE);
		mem_block_ptr-> free = true;
}

int main(int argc, char **argv[]) {
		char *str;
		str = (char *) malloc(18);
		strcpy(str,"hey look, I work!");
		printf("String = %s Address = %u\n",str,str);

		free(str);
		return 0;
}
