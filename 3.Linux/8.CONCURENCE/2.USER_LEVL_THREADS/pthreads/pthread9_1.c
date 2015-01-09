//usage of PTHREAD_(GET/SET)SCHEDPARAM..(DYNAMIC APPROACH) at runtime u can change the priority and policy and schedparams for any num of timess..


#include<stdio.h>
#include<pthread.h>

#include<stdlib.h>

#include<errno.h>

void *threadFunc(void *arg){

	printf("thread created,tid= %lu\n",pthread_self());
	sleep(10);
//	exit(EXIT_SUCCESS); if u give it here after execution of threadFunc it forcebly terminates..

}


print_schedparams(int *ptr_policy, struct sched_param *ptr_param){

	switch(*ptr_policy){
	
			case SCHED_FIFO:
					printf("policy: FIFO\npriority: %d\n",ptr_param->sched_priority);
					break;
			
			case SCHED_RR:
					printf("policy: RR\npriority: %d\n",ptr_param->sched_priority);
					break;

			case SCHED_OTHER:/*for SCHED_OTHER*/
					printf("policy: Other\npriority: %d\n",ptr_param->sched_priority);
					break;
			default: ;
					
			}

}

void change_schedparams(/*struct sched_param param,*/pthread_t tid,int policy,int prio){

	struct sched_param param;
	param.sched_priority = prio;
	
	//if(errno = pthread_setschedprio(tid,8)) perror("pthread_setschedprio");  //u can use this also but to change piority only.. BUT HERE CASE IT NOT WORKING(I DONT KNOW WHY?)
		
	if(errno = pthread_setschedparam(tid,policy,&param)) perror("pthread_setschedparam"),exit(1);


}

main(){

	pthread_t tid;
	pthread_attr_t attr;
	
	int policy;
	struct sched_param param;
	
	pthread_attr_init(&attr);

	pthread_create(&tid,&attr,threadFunc,NULL);
	
	sleep(1);
	
	/*printing default schedparams*/	
	pthread_getschedparam(tid,&policy,&param);
	print_schedparams(&policy,&param);
	printf("\n");

	/*changing default schedparams & printing d changes*/
	change_schedparams(/*param,*/tid,SCHED_RR,3);  //U MUST BE SUDO USER(PRIVILEGED USER)
	pthread_getschedparam(tid,&policy,&param); //U NEED TO GET AND THEN PRINT..
	print_schedparams(&policy,&param);	
	printf("\n");	

//	pause();  //if u put it then u must put exit(EXIT_SUCCESS) in print_schedparams func(since it is the last point of executn ), otherwise main thread will be in waiting state..

	change_schedparams(tid,SCHED_FIFO,89);
	pthread_getschedparam(tid,&policy,&param);
	print_schedparams(&policy,&param);	

	exit(EXIT_SUCCESS);
}
