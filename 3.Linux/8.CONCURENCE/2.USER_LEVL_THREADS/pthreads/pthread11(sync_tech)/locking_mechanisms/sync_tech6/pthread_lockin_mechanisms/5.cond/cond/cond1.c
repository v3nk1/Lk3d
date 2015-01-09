#include <stdio.h>
#include <pthread.h>
#include <signal.h>

int flag;

pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void *condsig(void *arg){

	printf("%s: Created\n",__func__);
	printf("%s: Sleeping for 10sec\n",__func__);
	//pthread_kill(*(pthread_t *)arg,SIGRTMAX);	//Spurious wakeup will happen
	sleep(10);
	
	printf("%s: Signaling..\n",__func__);
	flag=1;
	pthread_cond_signal(&cond);
}

void *condwait(void *arg){

	printf("%s: Created\n",__func__);
	printf("%s: Waiting for a signal\n",__func__);
	
	/*
	 * To avoid Spurious wakeups we shud use some logic(flag);
	 * Whenever the a thread triggers pthread_cond_signal, it will make one flag LOW to HIGH.
	 
	 * Inorder to avoid spurious wakeups, we shud check the flag HIGH'd by the thread.
	 */
	while(!flag){
		pthread_cond_wait(&cond,&mutex);
				/*
				 * 3 jobs done by cond_wait():
				 * 1.unlock the mutex
				 * 2.sleep (suspend) until hit by signal
				 * 3.locks the mutex
				 */

			/*
			 * It wont waste a CPU slice, B'coz using pthread_cond_wait() will 
			 * suspend(go to sleep) until it got hit by a signal.

			 * Without this pthread_cond_wait() also we can achieve it, bcoz we are using a flag.
			 * But the CPU slice will keep on wasting, since it will polls continuously.
			
			 * Without this while() loop also we can achive functionality, but
			 * Spurious wakeups may be possible.
			 */	
		}
	printf("%s: Got a signal\n",__func__);

}

main(){

	pthread_t tid1,tid2;
	pthread_mutex_init(&mutex,NULL);

	pthread_create(&tid1,NULL,condwait,NULL);
	pthread_create(&tid2,NULL,condsig,&tid1);

	pthread_exit(NULL);
}
