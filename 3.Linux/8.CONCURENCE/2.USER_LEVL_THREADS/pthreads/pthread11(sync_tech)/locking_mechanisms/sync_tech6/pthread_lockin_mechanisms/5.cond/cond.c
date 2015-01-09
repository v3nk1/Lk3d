#include<stdio.h>
#include<pthread.h>

void *threadFunc(void *arg){

	printf("thread created\n");
	
}

main(){

	pthread_t tid1,tid2;

	pthread_create(&tid1,NULL,threadFunc,NULL);
	pthread_create(&tid2,NULL,threadFunc,NULL);

}
