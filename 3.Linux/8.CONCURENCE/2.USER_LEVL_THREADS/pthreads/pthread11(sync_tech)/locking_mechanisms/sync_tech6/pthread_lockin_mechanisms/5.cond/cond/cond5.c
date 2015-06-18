/*
 * Qtn: An array of containing 100 ele, 2 threads one printing
	even offsets of array and another odd offsets. And try to 
	synchronize them using condition variables, even and odd offesets
	shud print respectively
 */

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mtx;
pthread_cond_t cond1=PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2=PTHREAD_COND_INITIALIZER;

#define SIZE 10
int a[SIZE];
int ev,od;

void *eve(void *arg){

	int i;
	printf("%s: Invoked\n",__func__);
	for(i=0;i<SIZE/2;i++){
		pthread_mutex_lock(&mtx);
		printf("In %s: [%d] is %d\n",__func__,2*i,a[2*i]);
		ev=0;od=1;
		if(od)
			pthread_cond_broadcast(&cond2);
		while(od)
			pthread_cond_wait(&cond1,&mtx);
		pthread_mutex_unlock(&mtx);
		}

}

void *odd(void *arg){

	int i;
	for(i=0;i<SIZE/2;i++){
		pthread_mutex_lock(&mtx);
		while(ev)
			pthread_cond_wait(&cond2,&mtx);
		printf("In %s: [%d] is %d\n",__func__,2*i+1,a[2*i+1]);
		ev=1;od=0;
		pthread_mutex_unlock(&mtx);
		if(ev)
		pthread_cond_signal(&cond1);
		}

}

main(){
	
	int i;
	pthread_t tid1,tid2;
	pthread_mutex_init(&mtx,NULL);
	for(i=0;i<SIZE;i++)
		a[i]='A'+i;

	pthread_create(&tid1,NULL,eve,NULL);

	pthread_mutex_lock(&mtx);
	pthread_cond_wait(&cond2,&mtx);
	pthread_mutex_unlock(&mtx);

	pthread_create(&tid2,NULL,odd,NULL);

	pthread_exit(NULL);

}
