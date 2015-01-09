//binary semaphore problem1: ACCEDENTAL RELEASE..
/*
  ACCEDENTAL RELEASE:
		scenario:
			1) thread1 and thread2 are threre, thread1 is for updating the data..
			  thread2 is for reading the updated/previous data but not stalled data..
		
			2) Here thread1 locked and updating the data, in the middle of updation its cpu time slice is overed,then 			    the cpu slice given to thread2,so thread2 shuld wait but here thread2 unlocks the sem object using 				      sem_post function, and accessing data..
	
			Actually it shuld wait until thread1 unlocks it and access the updated data..
			So this behaviour makes problem..
			its called accedental release.
	*/

#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>

#include<signal.h>

struct glob{
	int a;
	int b;
	}obj;

sem_t sem;

void *threadFunc1(void *arg){//updating

	printf("thread1 has created, tid = %lu\n",pthread_self());

	printf("thread1 locked the semaphore\n");
	sem_wait(&sem); //locking
	obj.a = 10;
	sleep(5); //it supends..
	obj.b = 20;
	sem_post(&sem);//non execute statement	
	printf("thread1 unlocked the semaphore\n");

}

void *threadFunc2(void *arg){//for reading glob data

	printf("thread2 has created, tid = %lu\n",pthread_self());
	
	sem_post(&sem);//it is unlocking the thread1 lock and accessing the global shared dataa..

	sem_wait(&sem);
 
	printf("mem1:%d\n",obj.a);
	printf("mem2:%d\n",obj.b);
	
	sem_post(&sem);

}

main(int argc,char *argv[]){

	sem_init(&sem,0,1);//initial state will be unlock,becoz of third arg is 1;
	
	pthread_t tid1,tid2;

	pthread_create(&tid1,NULL,threadFunc1,NULL);
	sleep(1);
	pthread_create(&tid2,NULL,threadFunc2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

}
