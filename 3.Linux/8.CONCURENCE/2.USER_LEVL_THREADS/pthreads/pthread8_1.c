//printing the present thread scope using "pthread_getattr_np" function..

//changing the thread attributes_SCOPE.. IN LINUX IT CANNT BE CHANGED SCOPE IS ALWAYS: PTHREAD_SCOPE_SYSTEM..
	
#define _GNU_SOURCE

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define SYSTEM PTHREAD_SCOPE_SYSTEM   // defined for simple use of ternary operator..
#define PROCESS PTHREAD_SCOPE_PROCESS

void *threadFunc(void *arg){

	printf("thread created\n");

}

void check_scope(pthread_attr_t *attr){

	int scope;

	pthread_attr_getscope(attr,&scope); // why we are using it again *****************************************************??
	
	printf("%s\n", scope == SYSTEM ? "system scope" : "process scope");

	exit(EXIT_SUCCESS); //for to came out of pass we used this exit heree.. otherwise the main thread will wait-state.
}

main(){

	int scope;

	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);	
	
	pthread_create(&tid,&attr,threadFunc,NULL);
	
	sleep(1);  //giving a chance to child thread by suspending parent thread..
	
	pthread_getattr_np(tid,&attr);
	
	check_scope(&attr);	
//	pthread_join(tid,NULL);

	pause(); //this will wait the main thread untill all other threads to terminate or till a signal came.. 

}
