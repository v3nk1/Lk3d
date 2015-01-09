//reading from a shared mem , first 3.write.c shud be run before only run this

#include "headers.h"

#include <sys/mman.h>

main(){

	int shmid = shmget(KEY,8/*getpagesize()*/,IPC_CREAT);
	if(shmid == -1) perror("shmget"),exit(1);
	
	printf("shmid: %lu\n",shmid);
		
	void *shmaddr = shmat(shmid,NULL,0);
	if(shmaddr == (void *)-1){
			perror("shmat"); //must it tell why error.. make sure u are "sudo" user..
			exit(2);
			}
		
	printf("read: %d\n",*((int *)shmaddr)); // u get a write value if u invoke this after writing in the shared mem is done, otherwise 0 will be readed..
	
	if(shmdt(shmaddr)== -1) perror("shmdt");

}
