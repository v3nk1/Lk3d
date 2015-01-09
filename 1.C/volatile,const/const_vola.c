#include <stdio.h>

int main(void)
{

	volatile const int local = 10;
	int shmfd=shm_open("/const_vola",O_CREAT|O_RDWR,0666);
	ftruncate(shmfd,sizeof(local));
	mmap(NULL,sizeof(local),PROT_READ|PROT_WRITE,MAP_SHARED,shmfd,0);
//    int *ptr = (int*) &local;

	printf("Initial value of local : %d \n", local);

	local = 20;
//    *ptr = 100;

	printf("Modified value of local: %d \n", local);

	return 0;

}
/*Incomplete*/
