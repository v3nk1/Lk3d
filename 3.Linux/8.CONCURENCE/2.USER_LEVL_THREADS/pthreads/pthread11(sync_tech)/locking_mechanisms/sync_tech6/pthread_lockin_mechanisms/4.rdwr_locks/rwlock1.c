//pthread_mutex problem: if 1 writer and 3 readers

#include<stdio.h>
#include<pthread.h>

struct glob{
	int a;
	int b;
	}obj;

pthread_mutex_t mutex;

void *writer(void *arg){

	printf("writer-thread has created: %lu\n",pthread_self());
	pthread_mutex_lock(&mutex);
	obj.a = 10;
	pthread_exit(NULL);
	sleep(1);
	obj.b = 20;
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *reader1(void *arg){

	printf("reader1 has created: %lu\n",pthread_self());

	pthread_mutex_lock(&mutex);
	pause();
	printf("rd1 : member1: %d\n",obj.a);
	printf("rd1 : member2: %d\n",obj.b);
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

void *reader2(void *arg){

	printf("reader2 has created: %lu\n",pthread_self());

	pthread_mutex_lock(&mutex);
	pause();
	printf("rd2 : member1: %d\n",obj.a);
	printf("rd2 : member2: %d\n",obj.b);
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

void *reader3(void *arg){

	printf("reader3 has created: %lu\n",pthread_self());

	pthread_mutex_lock(&mutex);
	//pause(); here if no pause is given here, then also thread3 unable to read(shud blocked here) becoz in mutex only one can read or write
	printf("rd3 : member1: %d\n",obj.a);
	printf("rd3 : member2: %d\n",obj.b);
	pthread_mutex_lock(&mutex);
	
	return NULL;
}

main(){

	pthread_mutex_init(&mutex,NULL);

	pthread_t tid1,tid2,tid3,tid4;
	
	pthread_create(&tid1,NULL,writer,NULL);
	sleep(1);
	pthread_create(&tid2,NULL,reader1,NULL);
	pthread_create(&tid3,NULL,reader2,NULL);
	pthread_create(&tid4,NULL,reader3,NULL);

	pause();

}
