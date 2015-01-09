//getting a persistant global value by signal handler concept..

#include<stdio.h>
#include<pthread.h>

#include<signal.h>
#include<string.h>

int glob;
pthread_t thread1,thread2;

void *threadFunc(void *arg){

	int i;
	for(i=0;i<800000;i++)
	glob++;
}

void sigALARM(int signo){

	printf("caught signal:%d (%s)\n\n",signo,strsignal(signo));
	pthread_create(&thread2,NULL,threadFunc,NULL);
	//sleep(3);
}

main(){

	
	pthread_create(&thread1,NULL,threadFunc,NULL);
	printf("deflt thrd is suspnd for 2s so that child'll get a chance\n");
	sleep(2);	

	printf("\nafter 1st thread glob=%d\n",glob); 

	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_handler=sigALARM;
//	act.sa_flags = SA_RESTART;
	sigaction(SIGUSR1,&act,NULL);
	
	
	if(!pthread_join(thread1,NULL))	kill(getpid(),SIGUSR1); //when thrd1 has done its job, dis will deliver a alarm signal..

	pthread_join(thread2,NULL);

	printf("after 2nd thread glob=%d\n",glob); 

}

/*******************************************************************************************************************************
NOTES:
``````Here In this scenario using signal handlers we are achiving synchronization(getting a persistant data)..

      we are (invoking) or creating a thread2 if and only if the thread1 has completes its job(BY USING MAN 2 KILL() at run time)...
	
      Here to achive persistant data we are using signals concepts; In the general purpose signals(ie., first 32) there are 2 signals named as SIGUSR1,SIGUSR2.. these two are user definable signals.. you can use them here for event notification(that thread1 has complets its job)..

      Dont use and dont change default disposition of predefined signals like SIGINT,SIGQUIT,SIGALRM..

*******************************************************************************************************************************/
