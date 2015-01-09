//Test the effect of with/without the following clone flag CLONE_SIGHAND.

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
	while(1); //printf("In clone\n");    //dont put msg in while, since its very fast, u cant see the signalHandler message..
//	sleep(10);
}

void _SIGINT(int signo){

	printf("signal: %d (%s) is recieved\n",signo,strsignal(signo));
	//getchar();//exit(EXIT_SUCCESS);

}

void reg_sigHand(void){

	struct sigaction act;
	memset(&act,0,sizeof(act));
	
	act.sa_handler = _SIGINT;
	//act.sa_flags =SA_RESTART;//if signal arrived to child it comes out of while loop,if u want to resume work where it stopd\														use this flag.
	sigaction(SIGINT,&act,NULL);
}	

void reg_DFL(void){

	struct sigaction act;
	memset(&act,0,sizeof(act));
	
	act.sa_handler = SIG_DFL;
	sigaction(SIGINT,&act,NULL);

}

int main(){

	reg_sigHand();
		
	void *child_stack = malloc(STACK_SIZE);

	if(clone(threadFunc,child_stack+STACK_SIZE,/*CLONE_SIGHAND|*/CLONE_VM,NULL)==-1) perror("clone"); //comment & uncomment it\														and see output
													
	reg_DFL();

	getchar();

	return 0;   

}


/********************************************************************************************************************************
NOTES:
``````1)see without CLONE_SIGHAND it just inherits the parents signalHandlers(signal dispositions) which are before clone.. 
    observe the above example in that after clone we are changing disposition to default na..?
		then without this flag child cannt be aware of it. Child has still registed previous changed disposition only even if u change in parent also..
      2) with this flag CLONE_SIGHAND is passed then child also changes its disposition as parent changed.
      3) In this scenario child have a copy of parent signal dispositions which are before invoking of clone().
		after clone any change u made to signal dispositions those are not visible to child if u dont use this flag.
		if u use this flag, after clone signal information also shared to child.
      
SEE STATE OF THE PROCESSES IN "ps -el" (MAKE A HABIT OF IT).

********************************************************************************************************************************/

