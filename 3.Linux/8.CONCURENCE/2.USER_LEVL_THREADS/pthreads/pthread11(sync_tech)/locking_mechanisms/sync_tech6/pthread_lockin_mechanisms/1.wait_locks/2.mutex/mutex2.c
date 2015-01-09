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

	//Is this problem is addressed(rectified) in mutex or not? yes rectified..(using flag:PTHREAD_MUTEX_ERRORCHECK)
	//If u use default mutex then it is same as binary semaphore, so prob shud be there, so dont use default mutex..

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#include<errno.h> //for perrror

struct glob{
	int a;
	int b;
	}obj;

pthread_mutex_t mutex /*= PTHREAD_MUTEX_ERRORCHECK*/; //(static initialization)

void *threadFunc1(void *arg){//updating

	printf("thread1 has created, tid = %lu\n",pthread_self());

	printf("thread1 locked the semaphore\n");
	pthread_mutex_lock(&mutex); //locking
	obj.a = 10;
	sleep(5); //it supends..
	obj.b = 20;
	pthread_mutex_unlock(&mutex);//non execute statement in binary semaphore.. But here itwill execute after 5sec..
	printf("thread1 unlocked the semaphore\n");

}

void *threadFunc2(void *arg){//for reading glob data

	printf("thread2 has created, tid = %lu\n",pthread_self());

	/* This operation is not permited here, since in this type of mutex it will validate owener who has locked, the one who is locked is the only one who can unlock this type of mutex.(The owners id is stored in a mutex structure object) */	
	if(errno = pthread_mutex_unlock(&mutex)) perror("pthread_mutex_unlock");//it is unlocking the thread1 lock and accessing the global shared dataa..

	pthread_mutex_lock(&mutex);
 
	printf("mem1:%d\n",obj.a);
	printf("mem2:%d\n",obj.b);
	
	pthread_mutex_unlock(&mutex);	

}

main(int argc,char *argv[]){

	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_init(&mutexattr); //first initialise all values to default and change what entity u want to change..
	pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_ERRORCHECK);//set type of mutex dynamically

	pthread_mutex_init(&mutex,&mutexattr);
	
	pthread_t tid1,tid2;

	pthread_create(&tid1,NULL,threadFunc1,NULL);
	sleep(1);
	pthread_create(&tid2,NULL,threadFunc2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

}
