//changing the default detach-state

#define _GNU_SOURCE 

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

#include<errno.h>

void *thrd_func(void *msg){

	printf("entered to child thread\n");
	printf("%s",(char *)msg);   //dnt derefer it, bcoz %s needs just base address only na..??
		
}

void check_dstate(/*int *d_state*/pthread_t *thread){

/****************************************************************************************************************
THIS SWITCH CASE WORKS ONLY IF U CREATE A THREAD IN DETACHED OR JOINABLE STATE USING "PTHREAD_CREATE()" FUNCTION
	BUT HERE WE ARE DYNAMICALLY(ie., at runtime) WE ARE CHANGING THREAD FROM JOINABLE TO DETACH USING "PTHREAD_DETACH()"

		switch(*d_state){
	
			case PTHREAD_CREATE_DETACHED: 
							printf("created in detach state\n");
							break;

     	default: or	case PTHREAD_CREATE_JOINABLE:
							printf("creatd in joinable state\n");
							break;
				
			}

***********************************************************************************************************/

//THIS WORKS FOR ALL TYPES OF FUNCTIONS(ITS GENIRIC):
	if(!pthread_join(*thread,NULL)) printf("its in joinable\n"); //pthread_join retuns 0 if and only if d thread is joinable.
	else printf("its in detached state\n");

}

main(){

	pthread_t thread;

	pthread_attr_t tr_attr;
	pthread_attr_init(&tr_attr);
	
//	int d_state=0;


	pthread_create(&thread,&tr_attr,thrd_func,"Now i'm doing detach-state\n");

	pthread_attr_destroy(&tr_attr);
	sleep(2);//we are giving to child thread to execute by suspending parent thread by 10 sec.. we cann't use bellow one since			its a detached thread.
//	d_state=0;
//	pthread_attr_getdetachstate(&tr_attr, &d_state);
	check_dstate(/*&d_state*/&thread);

	if(!pthread_detach(thread)) printf("pthread_detach: failed\n"),exit(1234); //put exit(value) to know where it failed.By pressing $? in shell prompt it will print value where the program stoped coz of error..



//	pthread_attr_destroy(&tr_attr);
//	d_state=0;
//	pthread_attr_getdetachstate(&tr_attr, &d_state);
	check_dstate(/*&d_state*/&thread);
	
exit(EXIT_SUCCESS);
}


/********************************************************************************************************************************
NOTES:
``````
	In above check_dstate() func switch case wont work..
	To decide its changed to detach state from join state, we use above geniric approach..

	we can conv a thread from joinable to detach
	but can't conv from detach to join..

*********************************************************************************************************************************/
