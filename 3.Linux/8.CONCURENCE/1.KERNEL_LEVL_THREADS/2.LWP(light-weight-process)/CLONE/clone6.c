//Test the effect of with/without the following clone flag CLONE_PARENT.

#define _GNU_SOURCE

#include<sched.h>

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define STACK_SIZE 12000

#include<string.h>
#include<signal.h>

int threadFunc(void *arg){

	printf("clone created\n");
	while(1) printf("In clone\n");

}

void _SIGINT(int signo){

	printf("signal: %d (%s) is recieved\n",signo,strsignal(signo));
	exit(EXIT_SUCCESS);

}

void reg_sigHand(void){

	struct sigaction act;
	memset(&act,0,sizeof(act));
	
	act.sa_handler = _SIGINT;
	sigaction(SIGINT,&act,NULL);
}	

int main(){

	reg_sigHand();
		
	void *child_stack = malloc(STACK_SIZE);

	if(clone(threadFunc,child_stack+STACK_SIZE,CLONE_PARENT|CLONE_SIGHAND|CLONE_VM,NULL)==-1) perror("clone");
	getchar();
	return 0;   // dnt know why CLONE_SIGHAND???	
}

//The change what i've observed whn u pass CLONE_PARENT is the childs ppid is same as parents ppid.
