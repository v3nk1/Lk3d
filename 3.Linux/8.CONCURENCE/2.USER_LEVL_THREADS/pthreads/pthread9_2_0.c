//usage of pthread_attr_(set/get)inheritsched():all attr_set/get functions are statical approaches..
//printing default values:

#include<stdio.h>
#include<pthread.h>

void *threadFunc(void *arg){

	printf("thread has created\n");
	sleep(10);

}

void print_schedparams(pthread_t tid){

	int policy;
	struct sched_param param;
	pthread_getschedparam(tid,&policy,&param);

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
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	
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
