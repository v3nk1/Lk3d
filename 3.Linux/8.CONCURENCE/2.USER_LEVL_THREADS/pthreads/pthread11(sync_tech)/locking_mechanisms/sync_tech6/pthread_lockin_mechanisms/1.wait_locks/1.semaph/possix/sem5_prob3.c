//BINARY SEMAPHORE PROBLEM3: RECURSIVE LOCKING.. (it again causes dead lock state)
	// here it(func) is trying to lock a semaphore which is already locked by a thread(1 or 2), so it causes waiting forever in func at sem_wait instruction..

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

struct glob{
	int a;
	int b;
	} obj;


sem_t sem;

void func(void){

	printf("In the func:\n");

	sem_wait(&sem); // it will wait here forever..
	obj.a=1000;
	obj.b=2000;
	sem_post(&sem);
	
}

void *threadFunc1(void *arg){

	printf("thread1: %lu has created\n",pthread_self());

	sem_wait(&sem);
	printf("thread1 is doing its job\nCalled to func\n");
	func();
	sem_post(&sem);
}

void *threadFunc2(void *arg){

	printf("thread2: %lu has created\n",pthread_self());

	sem_wait(&sem);
	printf("thread2 is doing its job\nCalled to func\n");
	func();
	sem_post(&sem);
	
}

void main(void){

	sem_init(&sem,0,1);//binary semaphore

	pthread_t tid1,tid2;

	pthread_create(&tid1,NULL,threadFunc1,NULL);
	pthread_create(&tid2,NULL,threadFunc2,NULL);
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

}
