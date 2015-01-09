//use of semaphore for event notify instead of signal handlers

//in this we are implementing event notify using signal handlers..

#include<signal.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#include<string.h>

#include<errno.h>

void sigHand(int signo){  //i dont know why my handler is not invoking??

	printf("caught signal %d (%s) for event notification\n",signo,strsignal(signo));

}

void regEVENTsig(void){

	struct sigaction act;
	memset(&act,0,sizeof(act));
	
	act.sa_handler = sigHand;
//	act.sa_flags = SA_RESTART;
	
	sigaction(SIGUSR1,&act,NULL);

}

void *threadFunc1(void *tid2){
	
	printf("thread1 has created\n");

	sleep(3);  //if thread1 creates first then thread2 will be in block forever. to avoid that i'm giving sleep..

	if(errno = pthread_kill(*(pthread_t *)tid2,SIGUSR1)) perror("pthread_kill");
	printf("deliverd a event signal to thread2\n");
		
	pthread_exit(NULL);

}

void *threadFunc2(void *arg){

	printf("thread2 has created\n");

	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGUSR1);

	sigwaitinfo(&set,NULL);// here thread2 will block until thread1 sent a signal SIGUSR1;
	
	printf("event signal has recieved from thread1\n");
	
	pthread_exit(NULL);

}

main(){

	pthread_t tid1,tid2;

	regEVENTsig(); //user defined signal registration
	
	pthread_create(&tid1,NULL,threadFunc1,&tid2);
//	sleep(1);
	pthread_create(&tid2,NULL,threadFunc2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);


}	
