//BINARY SEMAPHORE PROBLEM3: RECURSIVE LOCKING.. (it again causes dead lock state)

	// here it(func) is trying to lock a semaphore which is already locked by a thread(1 or 2), so it causes waiting forever in func at sem_wait instruction..

	//Is this problem is addressed(rectified) in mutex or not? yes rectified..(using flag:PTHREAD_MUTEX_ERRORCHECK)
        //If u use default mutex then it is same as binary semaphore, so prob shud be there, so dont use default mutex..

#include<stdio.h>
#include<pthread.h>

#include<errno.h> //for perror

struct glob{
	int a;
	int b;
	} obj;


pthread_mutex_t mutex/*=PTHREAD_MUTEX_ERRORCHECK*/;  //for static approach of mutex intialization

void func(void){

	printf("In the func:\n");

	if(errno = pthread_mutex_lock(&mutex)) perror("pthread_mutex_lock"); // it will wait here forever in binary semphore, but here if fails and throws an error..
	obj.a=1000;
	obj.b=2000;
	pthread_mutex_unlock(&mutex);
	
}

void *threadFunc1(void *arg){

	printf("thread1: %lu has created\n",pthread_self());

	pthread_mutex_lock(&mutex);
	printf("thread1 is doing its job\nCalled to func\n");
	func();
	pthread_mutex_unlock(&mutex);
}

void *threadFunc2(void *arg){

	printf("thread2: %lu has created\n",pthread_self());

	pthread_mutex_lock(&mutex);
	printf("thread2 is doing its job\nCalled to func\n");
	func();
	pthread_mutex_unlock(&mutex);
	
}

void main(void){

	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_init(&mutexattr);

	pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_ERRORCHECK);
		
	pthread_mutex_init(&mutex,&mutexattr);

	pthread_t tid1,tid2;

	pthread_create(&tid1,NULL,threadFunc1,NULL);
	sleep(1);
	pthread_create(&tid2,NULL,threadFunc2,NULL);
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

}
