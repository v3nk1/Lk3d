//to understand semaphore(binary).. how its used to synchronise and get a persistant data instead of stalled(half updated)data..

//demonstrated using a global object of a structure. //here in this i dont want to read the stalled data, i want to read the previous data or updated data but not half updated data..

//TO UNDERSTAND THESE CONCEPTS PLEASE COME ACROSS THE PREVIOUS SESSIONS OF SYNCHRONIZATION CONCEPTS..(FROM STARTING of "sync_tech" directory)

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

struct glob{
	int a;
	int b;
	}obj;

sem_t sem;

//sem_init(&sem,0,1); we cannt intialise it here(bcoz any function is invoked under a process only, use it in the threadFuncs or in main(default) thread)

void *treadFunc1(void *arg){  //updating the members of structure

	printf("thread1 has created\n");
	
	int p;
//	sem_getvalue(&sem,&p);	
//	printf("sem_b = %d\n",p);
	sem_wait(&sem);
//	sem_getvalue(&sem,&p);	
//	printf("sem_a = %d\n",p);
	obj.a = 10;
	sleep(2); //to make sure that i'm giving a chance to get a stalled data..
	obj.b = 20;
	sem_post(&sem);

	pthread_exit(NULL);

}

void *treadFunc2(void *arg){// reading the members of the structure

	printf("thread2 has created\n");
	
	sem_wait(&sem);
	printf("member1: a = %d\n",obj.a);
	printf("member2: b = %d\n",obj.b);
	sem_post(&sem);

	pthread_exit(NULL);

}

main(){

	sem_init(&sem,0,1);//initialization of semaphore(MUST AND SHUD)..
	
	pthread_t tid1,tid2;  
	
	pthread_create(&tid1,NULL,treadFunc1,NULL);
	
	sleep(1);  //by this sleep i'm giving a chance to thread1 execution., and dont affraid i gave a sleep inbetween the updation of member1 and member2 to get a stalled data..
	
	pthread_create(&tid2,NULL,treadFunc2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

//	pause();

}	
