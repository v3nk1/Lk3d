//usage of pthread_attr_(set/get)inheritsched():all attr_set/get functions are statical approaches..
//changing default values:

#include<stdio.h>
#include<pthread.h>

#include<errno.h>  //for perror usage

void *threadFunc(void *arg){

	printf("thread has created\n\n");
	sleep(10);

}

void print_schedparams(pthread_t tid){

	int policy;
	struct sched_param param;
	if(errno = pthread_getschedparam(tid,&policy,&param)) perror("pthread_getschedparam"),exit(9);

	switch(policy){
			case SCHED_OTHER:
						printf("policy:Other\npriority:%d\n",param.sched_priority);
						break;
			case SCHED_FIFO :
						printf("policy:FIFO\npriority:%d\n",param.sched_priority);
						break;
						
			case SCHED_RR   :
						printf("policy:RR\npriority:%d\n",param.sched_priority);
						break;

				default         : 
						printf("error\n");
						exit(10);
		}
	printf("\n");
}		

void check_inheritsched(pthread_t tid,int *inheritsched){

	switch(*inheritsched){
	
		case PTHREAD_INHERIT_SCHED:
						printf("child inheriting sched params from parent\n");
						print_schedparams(tid);
						break;
		case PTHREAD_EXPLICIT_SCHED:	
						printf("child has its own shced params\n");
						printf("u must be a root user to change priorities\n");
						print_schedparams(tid);
						break;
		default			   :	
						printf("error in attributes\n");
						exit(11);
						break;
			}
	
}

main(){

	int inheritsched;
	struct sched_param param;
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	
	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED); 
			/*SEPARITING CHILD THREAD SCHEDPARMS(its goin to hv its own)*/

	pthread_attr_setschedpolicy(&attr,SCHED_FIFO);
	param.sched_priority = 73;  
		 // TO CHANGE IT YOU MUST BE A PRIVELLEGED USER(ROOT), use sudo ./a.out
	if(errno = pthread_attr_setschedparam(&attr,&param)) perror("pthread_attr_setschedparam"),exit(12);
		 //if u are not root user it will throw an error..

	pthread_create(&tid,&attr,threadFunc,NULL);
	sleep(1);
	pthread_attr_destroy(&attr);
	
	printf("PARENT THREAD SCHED PARAMS\n"); //printing main thread sched params
	print_schedparams(pthread_self()); 
	
	pthread_attr_getinheritsched(&attr,&inheritsched);
	check_inheritsched(tid,&inheritsched);

	printf("main thread is in paused state press 'ctrl+c':\n");	
	pause();   //press ctrl+c at last.. to come out of pause..
	
}
