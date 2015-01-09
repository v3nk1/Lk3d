//to understand semaphore(binary).. how its used to synchronise and get a persistant data instead of stalled(half updated)data..

//demonstrated using a global variable of int type..

//TO UNDERSTAND THESE CONCEPTS PLEASE COME ACROSS THE PREVIOUS SESSIONS OF SYNCHRONIZATION CONCEPTS..(FROM STARTING of "sync_tech" directory)

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int glob;
sem_t sem;

//sem_init(&sem,0,1); we cannt intialise it here(bcoz any function is invoked under a process only, use it in the threadFuncs or in main(default) thread)

void *treadFunc1(void *arg){

	printf("thread1 has created\n");
	
	int i=0;
	int p;
//	sem_getvalue(&sem,&p);	
//	printf("sem_b = %d\n",p);
	sem_wait(&sem);
//	sem_getvalue(&sem,&p);	
//	printf("sem_a = %d\n",p);
	while(i++<1000000) glob++;
	sem_post(&sem);

	pthread_exit(NULL);

}

void *treadFunc2(void *arg){

	printf("thread2 has created\n");
	
	int i=0;
	
	sem_wait(&sem);
	while(i++<1000000) glob++;
	sem_post(&sem);

	pthread_exit(NULL);

}

main(){

	sem_init(&sem,0,1);//initialization of semaphore(MUST AND SHUD)..
	
	pthread_t tid1,tid2;  
	
	pthread_create(&tid1,NULL,treadFunc1,NULL);
	
	//sleep(1);
	
	pthread_create(&tid2,NULL,treadFunc2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	printf("glob = %d\n",glob);
		
//	pause();

}	
