#include<stdio.h>
#include<signal.h>
#include<string.h>  //must otherwise %s throws segmentation fault..

void sigHandler(int no){

	printf("caught signal %d (%s)\n",no,strsignal(no));

}

main(){

	struct sigaction obj;
	memset(&obj,0,sizeof(obj));
	obj.sa_handler = sigHandler;
	obj.sa_flags = SA_RESETHAND;
	
	sigaction(SIGINT,&obj,NULL);
	
	//sleep(5);   //   sleep doesnt make sence here becoz, its comes out from sleep if a signal passed, even if u pass SA_RESTART.. actually SA_RESTART is used only for blocked system calls at kernel space only to start the terminated process where it was stopped.
	while(1); //while make sence..

}


/********************************************************************************************************************************

NOTES:
	when u press first time interrupt (^C) it will execute application defined signal handler, and becoz of SA_RESET flag is  	passed it automatically sets to DEFAULT action of the particular signal.
	so when 2nd press of (^C) it simply executes default action..

*********************************************************************************************************************************/
