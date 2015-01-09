//usage of PTHREAD_ATTR_(GET/SET)SCHEDPARAM.. (STATIC APPROACH) ie., after all u assign the required entity values to attributes object and create a pthread by passig the attribute object as argument..  
	//it can be used only one time.. we cant change the thread_attr at runtime.. since at the creation of thread only we must specify the sched_params(updated attr_t object).
// throug this function we cant change policies..
	

#include<stdio.h>
#include<pthread.h>

#include<stdlib.h>

#include<errno.h>

void *threadFunc(void *arg){

	printf("thread created,tid= %lu\n",pthread_self());
	sleep(10);
//	exit(EXIT_SUCCESS); if u give it here after execution of threadFunc it forcebly terminates..

}


void print_schedparams(struct sched_param *p_param){

					printf("policy: other\npriority: %d\n",p_param->sched_priority);
					
			}




main(){

	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	struct sched_param param;
	
	param.sched_priority = 3;
	
//	if(errno = pthread_attr_setschedpolicy(&attr,SCHED_FIFO)) perror("pthread_attr_setschedpolicy");
	if(errno = pthread_attr_setschedparam(&attr,&param)) perror("pthread_attr_setschedparam");

	pthread_create(&tid,&attr,threadFunc,NULL);
//	pthread_attr_distroy(&attr);
	memset(&param,0,sizeof(param));
	sleep(1);
	
	/*printing default schedparams*/
	pthread_attr_getschedparam(&attr,&param);
	print_schedparams(&param);
	printf("\n");

	/*changing default schedparams & printing d changes*/
/*	change_schedparams(tid,SCHED_RR,3);  //U MUST BE SUDO USER(PRIVILEGED USER)
	pthread_getschedparam(tid,&policy,&param); //U NEED TO GET AND THEN PRINT..
	print_schedparams(&policy,&param);	
	printf("\n");	

//	pause();  //if u put it then u must put exit(EXIT_SUCCESS) in print_schedparams func(since it is the last point of executn ), otherwise main thread will be in waiting state..

	change_schedparams(tid,SCHED_FIFO,89);
	pthread_getschedparam(tid,&policy,&param);
	print_schedparams(&policy,&param);	
*/
	exit(EXIT_SUCCESS);
}


/*============================================================================================
 * In sched other policy the priority must be 0. so it will neglect the priority even if u want to set.
 * perror will throw an error.
 */
