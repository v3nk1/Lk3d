//to understand semaphore errors.. //here u will get not contant output when u run multiple times.. to understand first read the text file s"em_readme.txt".

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int glob;
//sem_t sem; if u dont declare it here, see what will be happen in output

//sem_init(&sem,0,1); we cannt intialise it here(bcoz any function is invoked under a process only, use it in the threadFuncs or in main(default) thread)

void *treadFunc1(void *arg){

	sem_t sem; sem_init(&sem,0,1);
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

	sem_t sem;
	sem_init(&sem,0,1);
	printf("thread2 has created\n");
	
	int i=0;
	
	sem_wait(&sem);
	while(i++<1000000) glob++;
	sem_post(&sem);

	pthread_exit(NULL);

}

main(){

	//sem_init(&sem,0,1);//initialization of semaphore(MUST AND SHUD)..
	
	pthread_t tid1,tid2;  
	
	pthread_create(&tid1,NULL,treadFunc1,NULL);
	
	//sleep(1);  if u give sleep here then u are giving a chance to thread1 to complete its job before thread2 creation, here it may work since its just 1000000 so it will complete this num of loops in the given time slot(cpu slice given by scheduler) but what if the data is HUGE or NUM OF INSTRUCTIONs are huge then cpu slice will over in the middle of execution.. 
		// so to demonstrate that comment d sleep.
	
	pthread_create(&tid2,NULL,treadFunc2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	printf("glob = %d\n",glob);
		
//	pause();

}	

/******************************************************************************************************************************
NOTES:
``````
	Here in this case say thread1 is executed first then thread1 will lock its semaphore.. in the middle of execution its slice is over then thread2 will acquire cpu slice then thread2 started d execution(without completion of thread1 it is going to access the global data) Bcoz in thread1 you declare "sem_t sem" object locally(local to thread1 only,out of thread1 is not known), actually its locked..
		But in thread2 u r declared anothrer "sem_t sem" object locally(its also local to thread2 only,out of thread2 it not known).. so u are checking locked state of the ur local object so obviously its in unlock state..

	TO AVOID THIS BEHAVIOUR MAKE SURE THAT THE DECLARED SEM_T SEMAPHORE OBJECTS ARE GLOBAL, ITS YOUR RESPONSIBILITY..

*******************************************************************************************************************************/
