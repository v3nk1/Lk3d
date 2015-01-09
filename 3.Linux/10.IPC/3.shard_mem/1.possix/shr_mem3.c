//compile with "cc <name> -lpthread -lrt"
	//Again here we are accessing shared data between producer and consumer, so race conditions will occur(stalled data or inconsistent data), so again we need synchronization techniques and locking mechanisms(like semaphore or mutex) to avoid race conditions..

#include"headers.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *threadFunc1(void *offset){//writer

	printf("update thread has created: %lu\n",pthread_self());

	pthread_mutex_lock(&mutex);
	*((int *)offset) = 10;
	sleep(1);
	*((int *)offset +1) = 20;
	pthread_mutex_unlock(&mutex);

	return NULL;
}

void *threadFunc2(void *offset){//reader

	printf("reader thread has created: %lu\n",pthread_self());

	pthread_mutex_lock(&mutex);
	printf("mem1: %d\nmem2: %d\n",*((int *)offset),*((int *)offset +1));
	pthread_mutex_unlock(&mutex);

	return NULL;
}

main(){

	int fd;
	if((fd = shm_open("/shm1",O_RDWR|O_CREAT,0664)) == -1) perror("shm_open");
	
	if(ftruncate(fd,getpagesize())) perror("ftruncate");
	void *offset = mmap(NULL,getpagesize(),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	pthread_t tid1,tid2;

	pthread_create(&tid1,NULL,threadFunc1,offset);
	pthread_create(&tid2,NULL,threadFunc2,offset);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

}
