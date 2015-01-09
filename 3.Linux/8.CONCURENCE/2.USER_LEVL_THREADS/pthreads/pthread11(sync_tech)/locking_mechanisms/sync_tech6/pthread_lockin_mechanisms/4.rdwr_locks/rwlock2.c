//pthread_rdwrlock: Usage..

#include<stdio.h>
#include<pthread.h>

struct glob{
	int a;
	int b;
	}obj;

pthread_rwlock_t rwlock;

void *writer(void *arg){

	printf("writer-thread has created: %lu\n",pthread_self());
	pthread_rwlock_wrlock(&rwlock);//its like binary semaphore(mutex) only 1 can lock(access) other shud be in block state until its unlocked(access completed).
	obj.a = 10;
	sleep(1);
	obj.b = 20;
	pthread_rwlock_unlock(&rwlock); //for these rwlock there is no unlock function for rdunlock & wrunlock separately..
			//see the man page of "pthread_rwlock_unlock"
	return NULL;
}

void *reader1(void *arg){

	printf("reader1 has created: %lu\n",pthread_self());

	pthread_rwlock_rdlock(&rwlock);//its like countable semaphore(no blocking for reading), more than one can lock at a time
	pause();
	printf("rd1 : member1: %d\n",obj.a);
	printf("rd1 : member2: %d\n",obj.b);
	pthread_rwlock_unlock(&rwlock); //for these rwlock there is no unlock function for rdunlock & wrunlock separately..
	
	return NULL;
}

void *reader2(void *arg){

	printf("reader2 has created: %lu\n",pthread_self());

	pthread_rwlock_rdlock(&rwlock);
	pause();
	printf("rd2 : member1: %d\n",obj.a);
	printf("rd2 : member2: %d\n",obj.b);
	pthread_rwlock_unlock(&rwlock); //for these rwlock there is no unlock function for rdunlock & wrunlock separately..
	
	return NULL;
}

void *reader3(void *arg){

	printf("reader3 has created: %lu\n",pthread_self());

	pthread_rwlock_rdlock(&rwlock);
//	pause();  but here not like previous prog
	printf("rd3 : member1: %d\n",obj.a);
	printf("rd3 : member2: %d\n",obj.b);
	pthread_rwlock_unlock(&rwlock); //for these rwlock there is no unlock function for rdunlock & wrunlock separately..
	
	return NULL;
}

main(){

	pthread_rwlock_init(&rwlock,NULL);

	pthread_t tid1,tid2,tid3,tid4;
	
	pthread_create(&tid1,NULL,writer,NULL);
	sleep(1);
	pthread_create(&tid2,NULL,reader1,NULL);
	pthread_create(&tid3,NULL,reader2,NULL);
	pthread_create(&tid4,NULL,reader3,NULL);

	pause();

}
