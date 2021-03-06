/* shows how to use shared memory
Version : 1.0
Author : Team -C
*/

# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/types.h>
#include "memkey.h"
main(){
	int shm_id,i;
	key_t key = IPC_KEY;
	void *sharedarea;
	int *intptr;
	shm_id = shmget(key,8000,IPC_CREAT|0777);
	if(shm_id <0){
		perror("shmget:");
		exit(1);
	}
	printf("shm_id = %d\n",shm_id);
	getchar();
	getchar();
}
