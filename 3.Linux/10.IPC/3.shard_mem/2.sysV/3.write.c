//writing into a shared memory

#include "headers.h"

#include <sys/mman.h>

main(){

	

	int shmid = shmget(KEY,8/*getpagesize()*/,IPC_CREAT);
	if(shmid == -1) perror("shmget"),exit(1);
	
	printf("shmid: %lu\n",shmid);
		
	void *shmaddr = shmat(shmid,NULL,0);
		
	*((int *)shmaddr) = 54321;

}
