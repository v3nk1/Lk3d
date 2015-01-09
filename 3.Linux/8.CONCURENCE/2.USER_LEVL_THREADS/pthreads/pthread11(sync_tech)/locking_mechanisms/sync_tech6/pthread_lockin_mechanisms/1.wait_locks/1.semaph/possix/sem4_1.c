//use of semaphore for event notify instead of signal handlers

//in this we are implementing event notify using semaphores..

#include<signal.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#include<string.h>

#include<errno.h>

sem_t sem;

void *threadFunc1(void *arg){
	
	printf("thread1 has created\n");
	
	sem_post(&sem); //we are unlocking it here(instead of p)

	printf("deliverd a event notified to thread2 by unlocking the semphore\n");
		
	pthread_exit(NULL);

}

void *threadFunc2(void *arg){

	printf("thread2 has created\n");

	sem_wait(&sem);//even if thread2 executes 1st it will block here untill thread1 unlocks it..(since we make semaphore initially in locked state by initialize it by 0(3rd arg) )..

	sleep(1);  //to print thread1 last printf first and the below printf last i've given a sleep here..

	printf("event notify has recieved from thread1\n");
	
	pthread_exit(NULL);

}

main(){

	sem_init(&sem,0,0);//so we are lockin the semaphore initially.. 
		//in previous semaphore examples we set semphore initially in unlock state by passing the 3rd argument as 1..
			// but here in this case only it is mandatory to set initially in lock state by passing 3rd arg as 0..
	
	pthread_t tid1,tid2;

	pthread_create(&tid1,NULL,threadFunc1,NULL);
//	sleep(1);
	pthread_create(&tid2,NULL,threadFunc2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

}	
