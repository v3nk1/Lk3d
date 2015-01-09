//Analyse the outputs

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#include<errno.h> 

int i;

pthread_mutex_t r_mutex=PTHREAD_MUTEX_INITIALIZER;


void *threadFunc1(void *arg){//updating

	printf("thread1 has created, tid = %lu\n",pthread_self());

	pthread_mutex_lock(&r_mutex); //locking
	i += 5;
	printf("1.i = %d\n",i);
	pthread_mutex_unlock(&r_mutex);

}

void *threadFunc2(void *arg){//for reading glob data

	printf("thread2 has created, tid = %lu\n",pthread_self());
	
	pthread_mutex_lock(&r_mutex);
	
	i += 4;
	printf("2.i = %d\n",i);
	
	pthread_mutex_unlock(&r_mutex);

}

main(int argc,char *argv[]){

	pthread_t tid1,tid2;
	pthread_mutex_lock(&r_mutex);

	pthread_create(&tid1,NULL,threadFunc1,NULL);
	pthread_create(&tid2,NULL,threadFunc2,NULL);
	i++;
	printf("i=%d\n",i);
	
	pthread_mutex_unlock(&r_mutex);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

}
