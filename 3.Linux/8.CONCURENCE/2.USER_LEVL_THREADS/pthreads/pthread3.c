// printing the present detach-state

#define _GNU_SOURCE 

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

void *thrd_func(void *msg){

	printf("entered to child thread\n");
	printf("%s",(char *)msg);   //dnt derefer it, bcoz %s needs just base address only na..??
	sleep(3);
}

main(){

	pthread_t thread;
	
	int d_state;

	pthread_attr_t tr_attr; //create an instace for setting our required attributes..
	pthread_attr_init(&tr_attr);// to set with default values, otherwise garbage values will be there.
	
	pthread_create(&thread,&tr_attr,thrd_func,"Now i'm doing detach-state\n");
	
	//sleep(2);//we are giving to child thread to execute by suspending parent thread by 10 sec.. or use bellow function

	pthread_attr_getdetachstate(&tr_attr, &d_state);
	switch(d_state){
	
			case PTHREAD_CREATE_DETACHED: printf("created in detach state\n");
							break;

			default:
				printf("creatd in joinable state\n");
				break;
				
			}

	pthread_join(thread,NULL);

exit(EXIT_SUCCESS);
}
