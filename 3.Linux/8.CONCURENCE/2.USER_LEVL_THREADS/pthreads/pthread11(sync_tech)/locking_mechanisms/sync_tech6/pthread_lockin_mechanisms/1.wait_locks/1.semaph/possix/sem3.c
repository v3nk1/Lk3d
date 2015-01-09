//to understand countable semaphore(not a binary).. how its used?
	/*The scenario:
	```````````````
		In this scenario:
			we are implementing online ticket booking.. here the availble seats are 5;
	*/
//TO UNDERSTAND THESE CONCEPTS PLEASE COME ACROSS THE PREVIOUS SESSIONS OF SYNCHRONIZATION CONCEPTS..(FROM STARTING of "sync_tech" directory)

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t sem;

//sem_init(&sem,0,1); we cannt intialise it here(bcoz any function is invoked under a process only, use it in the threadFuncs or in main(default) thread)

int cnt; // to display available seats..

void reserve(void){

	if(cnt > 0){

		printf("1.reserve a ticket\n2.exit\n");
		int temp;
		scanf("%d",&temp);
		if (temp == 1)	cnt--;
		
		else ;
	}
	
	else printf("no more seats: ******************* HOUSEFUL ****************** :");

	printf("available no of tickets: %d\n",cnt);

}


void *treadFunc1(void *arg){  

	sem_wait(&sem);
	printf("1client has came to book online ticket\n");
	
	int p;
//	sem_getvalue(&sem,&p);	
//	printf("sem_b = %d\n",p);
//	sem_getvalue(&sem,&p);	
//	printf("sem_a = %d\n",p);
	reserve();
	sem_post(&sem);

	pthread_exit(NULL);

}

void *treadFunc2(void *arg){

	sem_wait(&sem);
	printf("2nd client has came to book online ticket\n");
	
	reserve();
	sem_post(&sem);

	pthread_exit(NULL);

}

void *treadFunc3(void *arg){

	sem_wait(&sem);
	printf("3nd client has came to book online ticket\n");
	
	reserve();
	sem_post(&sem);

	pthread_exit(NULL);
}

void *treadFunc4(void *arg){

	sem_wait(&sem);
	printf("4nd client has came to book online ticket\n");
	
	reserve();
	sem_post(&sem);

	pthread_exit(NULL);
}

void *treadFunc5(void *arg){

	sem_wait(&sem);
	printf("5nd client has came to book online ticket\n");
	
	reserve();
	sem_post(&sem);

	pthread_exit(NULL);

}
void *treadFunc6(void *arg){
	if(cnt>0){
	sem_wait(&sem);
	printf("6nd client has came to book online ticket\n");
	
	reserve();
	sem_post(&sem);

	pthread_exit(NULL);
}}

main(){

	cnt = 5;
	sem_init(&sem,0,5);//initialization of semaphore(MUST AND SHUD).. it will be in unlock state until 5 locks invoked..
//means 5 sem_wait 's invoked then only semaphore value becomes to zero(lockd state).
	
	pthread_t tid1,tid2,tid3,tid4,tid5,tid6;
	
	pthread_create(&tid1,NULL,treadFunc1,NULL);
	pthread_create(&tid2,NULL,treadFunc2,NULL);
	pthread_create(&tid3,NULL,treadFunc3,NULL);
	pthread_create(&tid4,NULL,treadFunc4,NULL);
	pthread_create(&tid5,NULL,treadFunc5,NULL);
	pthread_create(&tid6,NULL,treadFunc6,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	pthread_join(tid4,NULL);
	pthread_join(tid5,NULL);
	pthread_join(tid6,NULL);

//	pause();

}


/*******************************************************************************************************************************
NOTES:
`````` In the above program i made a countable semaphore, by using sem_init and intialise its count to 5.
	
	means at max it can allow 5 clients at a time,after 5 client the semaphore is in locked state, it will be in locked state until one of the 5 clients(threads) has exited. if a 6th client came in locked state he will be in wait state until one of the client exit..

*******************************************************************************************************************************/	
