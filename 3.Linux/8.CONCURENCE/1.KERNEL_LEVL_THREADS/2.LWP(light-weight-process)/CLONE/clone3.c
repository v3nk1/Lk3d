//Is a file accessible by the parent when it was closed by child thread.?

#define _GNU_SOURCE

#include<stdio.h>
#include<sched.h>
#include<stdlib.h>

#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#define STACK_SIZE 12000

int fd;

void check_err(int ret, char *func){

	if(ret == -1) perror(func);
	else return;
	
}

int threadFunc(void *arg){

	printf("created a child(clone) process\n");
	check_err(close(fd),"close");

}

int main(){
	
	fd = open("./clone1.c",O_RDONLY);
	
	void *child_stack = malloc(STACK_SIZE);

	//int ret = clone(threadFunc, child_stack+STACK_SIZE ,CLONE_FILES|CLONE_FS,NULL); check_err(ret); these 2 steps in 1shot   	as bellow. for this i made check_err() function to genric, as above, see above...
	
	check_err(clone(threadFunc, child_stack+STACK_SIZE ,/*CLONE_FILES*/0,NULL),"clone");

	printf("parent went to sleep for 10sec\n");

	sleep(10);// must we shud wait untill child hav cpu slice.

	check_err(close(fd),"close");

	exit(EXIT_SUCCESS);	
	return 0;

}

/****************************************************************************************************************
NOTES:
``````see here if u pass a flag calld CLONE_FILES this the fd's also shared b/w parent and child, means child can close or read the data from a file opened in parent.
      			
			CLONE_VM = SHARES THE ADDRESS SPACE OF PARENT TO CHILD.
			CLONE_FILES = SHARES THE FILE DISCRIPTOR OF PARENT TO CHILD.

	Notice that: If u dont pass these flags it also behaves like parent & child as in fork()...

**************************************************************************************************************/
