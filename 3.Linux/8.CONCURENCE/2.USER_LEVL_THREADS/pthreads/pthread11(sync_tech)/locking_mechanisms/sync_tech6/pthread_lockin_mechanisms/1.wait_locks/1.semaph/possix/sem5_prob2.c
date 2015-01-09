//binary semaphore problem2: OWNER'S DEATH causes deadlock state..
	/*
		owner's death: 
				there are 2 threads thread1 and thread2, same as previous scenario, thread2 is in wait state becoz				of thread1 is locked the semaphore
				if the owner(who hav locked the semaphore) is died before unlocking it..(here thread1 is died)..
			      then thread2 is in wait state forever called DEADLOCK STATE..
		
				THIS PROBLEM OF SEMAPHORE CALLED OWNER'S DEATH..
	*/

#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>

#include<signal.h>

struct glob{
	int a;
	int b;
	}obj;

sem_t sem;

void *threadFunc1(void *arg){//updating

	printf("thread1 has created, tid = %lu\n",pthread_self());

	printf("thread1 locked the semaphore\n");
	sem_wait(&sem); //locking
	obj.a = 10;
	sleep(5);  //to make sure that thread2 has started before thread1 exits itself(to make thread2 in waiting state)..
//	abort();          		dnot use //this will terminates the default thread by throughing an error for coredump
//	pthread_cancel(pthread_self()); dnot use //since its not sure to cancel

	/*before it unlock the semaphore it is going to be exited by it self */
	pthread_exit(NULL);		//yes it will done ur expected job here..

//	exit(123);			dnot use //since direclty exits from default thread
//	raise(SIGTERM);			dont use //it sends the specified siganl to current process(but all signals are defaultly terminates main thread)
//	pthread_kill(pthread_self(),SIGKILL); dont use // its also same as above..

	//non execute statement
	obj.b = 20;
	sem_post(&sem);
	printf("thread1 unlocked the semaphore\n");

}

void *threadFunc2(void *arg){//for reading glob data

	printf("thread2 has created, tid = %lu\n",pthread_self());
	printf("waiting....\n");
	
	sem_wait(&sem); //it is expecting to thread1 will unlock the semaphore some time but it wont know that the thread1 killed it self.. SO IT CAUSES DEADLOCK STATE..
	printf("mem1:%d\n",obj.a);
	printf("mem2:%d\n",obj.b);
	
	sem_post(&sem);

}

main(int argc,char *argv[]){

	sem_init(&sem,0,1);//initial state will be unlock,becoz of third arg is 1;
	
	pthread_t tid1,tid2;

	pthread_create(&tid1,NULL,threadFunc1,NULL);
	sleep(1);
	pthread_create(&tid2,NULL,threadFunc2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

}
