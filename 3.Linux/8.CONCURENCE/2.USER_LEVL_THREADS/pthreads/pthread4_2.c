/*Create a detached thread & try to join it and observe the behaviour.
		hint: take the return values of pthread_join and put them in switch case.
*/

#include<stdio.h>
#include<pthread.h>

#include<errno.h> // becoz we are using EINVAL macro. its defined in errno.h

void *threadFunc(void *arg){

	printf("thread is created:\n");

}

void check_detach(pthread_t *thread){

	if(!pthread_join(*thread,NULL)) printf("Now thread is in joinable state\n");
	else printf("thread is in detached state\n");

}

main(){

	pthread_t thread;
	
	pthread_create(&thread,NULL,threadFunc,NULL);

	sleep(1);	
	check_detach(&thread);

	pthread_detach(thread);

	check_detach(&thread);
	
	if(pthread_join(thread,NULL)==ESRCH) printf("its in detached state, unable to join\n");

}


/********************************************************************************************************************************
NOTES:
------ If once u set into detach state its impossible to join again..

********************************************************************************************************************************/
