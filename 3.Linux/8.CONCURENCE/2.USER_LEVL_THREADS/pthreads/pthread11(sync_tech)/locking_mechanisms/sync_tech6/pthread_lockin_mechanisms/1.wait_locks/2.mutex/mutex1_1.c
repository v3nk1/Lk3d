//Using of mutex as a binary semaphore..(DYNAMIC APPROACH)..
//A mutex with default values acts as binary semaphore..

#include<stdio.h>
#include<pthread.h>

pthread_mutex_t mutex;	

struct glob{
	int a;
	int b;
	}obj;

void *updater(void *arg){
	
	printf("child thread has created for updating\n");
	pthread_mutex_lock(&mutex);
	obj.a=10;
	sleep(1);
	obj.b=20;
	pthread_mutex_unlock(&mutex);
	
	pthread_exit(NULL);
}

void *reader(void *arg){

	printf("child thread has created for reading\n");

	pthread_mutex_lock(&mutex);
	printf("mem1:%d\n",obj.a);
	printf("mem2:%d\n",obj.b);
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
	
}

void main(void){
	
	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_init(&mutexattr);
	
	pthread_mutex_init(&mutex,&mutexattr);

	pthread_mutex_destroy(&mutexattr);

	pthread_t tid1,tid2;

	pthread_create(&tid1,NULL,updater,NULL);
	sleep(1);
	pthread_create(&tid2,NULL,reader,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	
}
