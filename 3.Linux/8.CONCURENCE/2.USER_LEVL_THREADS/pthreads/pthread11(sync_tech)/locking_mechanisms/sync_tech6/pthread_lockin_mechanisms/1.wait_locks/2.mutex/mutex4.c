//binary semaphore problem2: OWNER'S DEATH causes deadlock state..
	/*
		owner's death: 
				there are 2 threads thread1 and thread2, same as previous scenario, thread2 is in wait state becoz				of thread1 is locked the semaphore
				if the owner(who hav locked the semaphore) is died before unlocking it..(here thread1 is died)..
			      then thread2 is in wait state forever called DEADLOCK STATE..
		
				THIS PROBLEM OF SEMAPHORE CALLED OWNER'S DEATH..
	*/

        //Is this problem is addressed(rectified) in mutex or not? yes rectified..But using flag: PTHREAD_MUTEX_ROBUST_NP;
			//but it will endup in reading stalled data.. we have to recover it manually..

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#include<errno.h> //for perror

struct glob{
	int a;
	int b;
	}obj;

pthread_mutex_t r_mutex;//robust mutex

void *threadFunc1(void *arg){//updating

	printf("thread1 has created, tid = %lu\n",pthread_self());

	printf("thread1 locked the semaphore\n");
	pthread_mutex_lock(&r_mutex); //locking
	obj.a = 10;
	sleep(5);  //to make sure that thread2 has started before thread1 exits itself(to make thread2 in waiting state)..
//	abort();          		dnot use //this will terminates the default thread by throughing an error for coredump
//	pthread_cancel(pthread_self()); dnot use //since its not sure to cancel

	/*before it unlock the semaphore it is going to be exited by it self */
	pthread_exit(NULL);		//yes it will done ur expected job here..

//	exit(123);			dnot use //since direclty exits from default thread
//	raise(SIGTERM);			dont use //it sends the specified siganl to current process(but all signals are defaultly terminates main thread)
//	pthread_kill(pthread_self(),SIGKILL); dont use // its also same as above..

	obj.b = 20; //non execute statements
	pthread_mutex_unlock(&r_mutex);
	printf("thread1 unlocked the semaphore\n");

}

void *threadFunc2(void *arg){//for reading glob data

	printf("thread2 has created, tid = %lu\n",pthread_self());
	printf("waiting....\n");
	
	if(errno = pthread_mutex_lock(&r_mutex)) perror("pthread_mutex_lock"); //it is expecting to thread1 will unlock the semaphore some time but it wont know that the thread1 killed it self.. SO IT CAUSES DEADLOCK STATE.. (in binary semaphore), but here it will fail..
	printf("mem1:%d\n",obj.a);
	printf("mem2:%d\n",obj.b);
	
	pthread_mutex_unlock(&r_mutex);

}

main(int argc,char *argv[]){

	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_init(&mutexattr);
	pthread_mutexattr_setrobust_np(&mutexattr,PTHREAD_MUTEX_ROBUST_NP);
	
	pthread_mutex_init(&r_mutex,&mutexattr);
	
	pthread_t tid1,tid2;

	pthread_create(&tid1,NULL,threadFunc1,NULL);
	sleep(1);
	pthread_create(&tid2,NULL,threadFunc2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

}
