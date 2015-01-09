//changing the default detach-state

#define _GNU_SOURCE 

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>


void *thrd_func(void *msg){

	printf("entered to child thread\n");
	printf("%s",(char *)msg);   //dnt derefer it, bcoz %s needs just base address only na..??
	sleep(1);	
	
}

void check_dstate(int d_state){

		switch(d_state){ //THIS SWITCH-CASE WORKS ONLY FOR STATICAL APROACH ONLY, SINCE WE ARE USING STATIC APPROACH FLAGS AS CASE CHECK... SEE THE NEXT PROGRAM..
	
			case PTHREAD_CREATE_DETACHED: 
							printf("created in detach state\n");
							break;

     	/*default: or*/	case PTHREAD_CREATE_JOINABLE:
							printf("creatd in joinable state\n");
							break;
				
			}
}

main(){

	pthread_t thread;
	int d_state;

	pthread_attr_t tr_attr; //create an instace for setting our required attributes..

	pthread_attr_init(&tr_attr);// to set with default values, otherwise garbage values will be there.
	
	pthread_attr_setdetachstate(&tr_attr,PTHREAD_CREATE_DETACHED); //SEE HERE WE ARE DECIDING IT STATICALLY,NEXT PROG IT WAS DECIDED AT RUNTIME(DYNAMICALLY)..
	
	pthread_create(&thread,&tr_attr,thrd_func,"Now i'm doing detach-state\n");
	
	sleep(2);//we are giving to child thread to execute by suspending parent thread by 10 sec.. we cann't use bellow one since			its a detached thread.

//	if(pthread_join(thread,NULL)) printf("detachstate\n"); we can use this also to check for detach state since this fuction works only if the thread is joinable, it fails if the thread is detachable.

	pthread_attr_getdetachstate(&tr_attr, &d_state);

	check_dstate(d_state);
	
exit(EXIT_SUCCESS);
}
