//create.. //u must be sudo user to invoke shared mem functions

#include "headers.h"

main(){

	int shmid = shmget(KEY,sizeof(int)*2,IPC_CREAT);
	if(shmid == -1) perror("shmget");
	
	printf("shmid: %lu\n",shmid);
		
	void *shmaddr = shmat(shmid,NULL,0);

}

//created shared mem can be seen in "sudo ipcs"..
