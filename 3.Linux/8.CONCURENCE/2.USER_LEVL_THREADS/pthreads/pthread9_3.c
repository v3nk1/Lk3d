//Create 2 threads 1 with FIFO and other with RR policy and with priorities 10 and 20 respectively. Print the scheduling attributes within the thread context.

#include<stdio.h>
#include<pthread.h>

#include<errno.h> //for perror usage

void *threadFunc(void *arg){

	printf("thread has created\n\n");
	sleep(10); //to make this thread in running state, in this gap functions will collect their information abt this thread.

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

	int inheritsched1,inheritsched2;
	struct sched_param param1,param2;
	pthread_t tid1,tid2;
	pthread_attr_t attr1,attr2;

	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);

/*must*/pthread_attr_setinheritsched(&attr1,PTHREAD_EXPLICIT_SCHED); //SEPARITING CHILD THREAD SCHEDPARMS(its goin to hv its own)
	pthread_attr_setinheritsched(&attr2,PTHREAD_EXPLICIT_SCHED);

	pthread_create(&tid1,&attr1,threadFunc,NULL);
	pthread_create(&tid2,&attr2,threadFunc,NULL);
	sleep(1);
	pthread_attr_destroy(&attr1);
	pthread_attr_destroy(&attr2);

	param1.sched_priority = 10;
	param2.sched_priority = 20;
	if(errno = pthread_setschedparam(tid1,SCHED_FIFO,&param1)) perror("pthread_setschedparam"),exit(12);//using this dynamic approach by 1func call we can set policy&prioity by1shot
	if(errno = pthread_setschedparam(tid2,SCHED_RR,&param2)) perror("pthread_setschedparam"),exit(13);
	
	
	printf("PARENT THREAD SCHED PARAMS\n"); //printing main thread sched params
	print_schedparams(pthread_self()); 
	
	pthread_attr_getinheritsched(&attr1,&inheritsched1);
	pthread_attr_getinheritsched(&attr2,&inheritsched2);
	check_inheritsched(tid1,&inheritsched1);
	check_inheritsched(tid2,&inheritsched2);
	
	printf("main thread is in paused state press 'ctrl+c':\n");
	pause();   //press ctrl+c at last.. to come out of pause..
	
}
