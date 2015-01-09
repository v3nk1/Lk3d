//Test the effect of with/without the following clone flag CLONE_VM.

#define _GNU_SOURCE

#include<sched.h>

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define STACK_SIZE 12000


int threadFunc(void *agr){

	printf("clone created\n");

}

main(){
	
	void *child_stack = malloc(STACK_SIZE);

	if(clone(threadFunc,child_stack+STACK_SIZE,CLONE_VM|CLONE_FILES,NULL)==-1) perror("clone");

}
