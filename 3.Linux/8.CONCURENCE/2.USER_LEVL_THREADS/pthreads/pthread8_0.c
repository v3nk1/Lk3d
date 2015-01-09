// Prog to printing the present scope of the thread using "pthread_attr_getscope"..

//changing the thread attributes_SCOPE.. IN LINUX IT CANNT BE CHANGED SCOPE IS ALWAYS: PTHREAD_SCOPE_SYSTEM..
	
#include<stdio.h>
#include<pthread.h>

#define SYSTEM PTHREAD_SCOPE_SYSTEM   // defined for simple use of ternary operator..
#define PROCESS PTHREAD_SCOPE_PROCESS

void *threadFunc(void *arg){

	printf("thread created\n");

}

void check_scope(int *scope){

/*	switch(*scope){
		case PTHREAD_SCOPE_SYSTEM: printf("system scope\n");
					   break;
		case PTHREAD_SCOPE_PROCESS: printf("process scope\n");
					    break;

				  default : ;
		}
*/
/*OR USE TERNARY OPERATOR INSTEAD OF SWITCH CASE*/
	
	printf("%s\n",*scope == SYSTEM ? "system scope" : "process scope");


}
main(){

	int scope;

	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);	
	
	pthread_create(&tid,&attr,threadFunc,NULL);
	
	sleep(1);  //giving a chance to child thread by suspending parent thread..
	
	pthread_attr_getscope(&attr,&scope);
	
	check_scope(&scope);	
	pthread_join(tid,NULL);
	
}
