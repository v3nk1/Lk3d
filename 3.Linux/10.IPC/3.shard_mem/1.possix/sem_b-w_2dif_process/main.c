#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include "mydata.h"

int main()
{
	int fd;
	unsigned int value = 1;
	struct mydata *addr=NULL;

	fd = shm_open(DATA, O_CREAT | O_RDWR,0666);
	if (fd == -1) {
		perror("shm_open");
		exit(1);
	}

	/* 4k is min shared memory */
	if (ftruncate(fd, getpagesize()) == -1) {
		perror("ftruncate");
		exit(1);
	}
	/* allocating data object in shared memory */
	addr = mmap(NULL, sizeof(struct mydata),
				  PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		perror("mmap");
		exit(2);
	}
	
	//Our intension here is to synchronize data without
	//opening semophore again and again in other processes.
	if(sem_init(&addr->sem,1,value) != 0)
				//0 for sharing among threads.
				//1 for sharing among processes.
		perror("sem_init");

	addr->a = 0;
	addr->b = 0;

	printf("%d: %d: %ld\n",addr->a,addr->b,addr->sem.__align);
				//see the sem_t structure in glibc source code.
	munmap(addr, sizeof(struct mydata));

	return 0;

}
