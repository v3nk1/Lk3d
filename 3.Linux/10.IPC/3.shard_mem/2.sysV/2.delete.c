//delete already created shared mem

#include "headers.h"

main(){

	int shmid =  shmget(KEY,8,IPC_CREAT);

	if(shmctl(shmid,IPC_RMID,NULL)) perror("shmctl");

}
