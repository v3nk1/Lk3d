// Process wil suspend(block) when its trying to subtract semaphore value from 0; 		\
   ie., blocked when semphore value tried to go negative

#include<stdio.h>
#include<math.h>
#include<sys/sem.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<pthread.h>
#include<string.h>

//#define RACECOND		 
				/*
				 * uncomment it for RACECONDTION or while compiling 
				 * cc sysV_sem.c -lpthread -DRACECOND
				 */

union semun {
	int val;    		 /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
	};

int i,semid;
struct sembuf s_lock = {0,-1};
struct sembuf s_ulock= {0,+1};

void *Func1(void *arg){

#ifndef RACECOND
	printf("tid1: Semaphore trying to lock..\n");
	semop(semid,&s_lock,1);
	printf("tid1: Semaphore locked..\n");
#endif
	i=10;
	sleep(1);
	printf("tid1: i value updated to %d\n",i);
#ifndef RACECOND
	printf("tid1: Semaphore trying to ulock..\n");
	semop(semid,&s_ulock,1);
	printf("tid1: Semaphore unlocked..\n");
#endif
	}

void *Func2(void *arg){

#ifndef RACECOND
	printf("tid2: Semaphore trying to lock..\n");
	semop(semid,&s_lock,1);
	printf("tid2: Semaphore locked..\n");
#endif
        i=20;
        sleep(1);
        printf("tid2: i value updated to %d\n",i);
#ifndef RACECOND
	printf("tid2: Semaphore trying to ulock..\n");
	semop(semid,&s_ulock,1);
	printf("tid2: Semaphore unlocked..\n");
#endif
        }
main(){

	union semun arg;
	memset(&arg,0,sizeof(arg));
	pthread_t tid1,tid2;
	semid = semget(555,1,IPC_CREAT|0666);
	arg.val=1;	

	if(semctl(semid,0,SETVAL,arg)<0)
		perror("semctl");

	pthread_create(&tid1,NULL,Func1,NULL);
	pthread_create(&tid2,NULL,Func2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
}
