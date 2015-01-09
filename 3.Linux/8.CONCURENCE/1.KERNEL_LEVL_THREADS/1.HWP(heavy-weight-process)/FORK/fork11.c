/*To understand this u must see "fork10_SIGCHLD.c" programm.

TO OVERCOME ZOMBIE STATE, & TO TELL THE SCHEDULAR THAT NO MORE SCHEDULE FOR CHILD cleanup required. for that-
	-parent shoud collect the exit state of child and inform to kernel.
	
	even child in zombie state(ie., kernel doesnt delete resouces na..) so it will have the PCB as it is. So the schedular will keep on scheduling it(zombie process) also.. so wastage of memory.
	
	COLLECTING THE EXIT STATE OF CHILD: 1) Asynchronous cleaner method. using Signal Handlers concept.

*/


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>


void cleanin_bySig(int signo){ // user defined signal handler for SIGCHLD.

	printf("1.signal:%d (%s) is recived\n",signo,strsignal(signo));
	wait(NULL); //if u want status pass an integer.
	printf("async clean acomplished successfully\n");	
}

void reg_SIGCHLD(){

	struct sigaction act;
	memset(&act,0,sizeof(act));
	
	act.sa_handler = cleanin_bySig;
/*x*/	act.sa_flags = SA_NOCLDSTOP | SA_RESTART; // THIS WILL BLOK THE SIGANLS 18,19.
	sigaction(SIGCHLD,&act,NULL);

}

void blck_SIGSTOP_SIGCONT(void){
/*
	sigset_t blck;
	sigemptyset(&blck);
	
	sigaddset(&blck,SIGSTOP);
	sigaddset(&blck,SIGCONT);
	
//	sigprocmask(SIG_BLOCK,&blck,NULL); it wont block the signals SIGSTOP.
*/

}
	
void disp_sent_sig(signo){ //it must be called in CHILD CONTEXT, since coz we are sending those signals to child pid only na..

	printf("2.signal:%d (%s) is recived ",signo,strsignal(signo));
	if(signo == 18|| signo == 19) printf("but ignored\n");
}   //if its invoked then the original signal for cleanup wont work. since default behaviour is changed.

main(){
	
	
	switch(fork()){

		case 0: /*CHILD CONTEXT*/

			printf("child context\n");

//			signal(SIGINT,disp_sent_sig); if u give these 3 statements, then SIGCHLD wont deliver,coz u r changing the default behaviour of signal to app defined handler.
//			signal(SIGCONT,disp_sent_sig);
//			signal(SIGSTOP,disp_sent_sig); //we cant register a handler for SIGSTOP..
	
			 struct sigaction act;
		         memset(&act,0,sizeof(act));
			
			//sleep(10);
			getchar();
			printf("child is terminated\n");
			break;
			
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
			break;

		default: /*PARENT CONTEXT*/

			printf("enters into parent context\n");

			reg_SIGCHLD();
			//blck_SIGSTOP_SIGCONT(); ITS ERROR.. NO USE OF IT,
			//cleanin_bySig(0); it shud given as a part of handler "reg_sigchld". not here.

			getchar();// to stop untill child termintes and to see the "ps -Af". since ZOMBIE process(defunc process) is created or not?
			printf("parent terminated\n");
			break;
		}

}

/********************************************************************************************************************************
NOTES:
``````	If u put 1 in comments (ie., 29 line) then if u pass SIGSTOP r SIGCONT also for SIGINT also cleanin_bySig() function wil b invoked. its an abnormal behaviour, becoz say SIGSTOP is deliverd, we can resume the signal by passing SIGCONT,but here in this case if u send any of the 3 signal the resouces allocated for the child is removed becoz each of this signal is invoking "cleanin_bySig()" function. In that we are provide a wraper function "wait()" sothat the parent collects the exitstate and remove those resouces. so we cant resume if u stop that process once.

	so we are now only interested in SIGINT only. if and only if the SIGINT is recieved then only we must clear the resources.

	So to avoid this behaviour we must pass a flag provided by sigaction API called SA_SIGNOCLDSTOP, actually this is the only one way, dont think that u can mask(BLOCK) the 2 signals SIGCONT,SIGSTOP since SIGSTOP is non blockable signal.

	so to do this we are passing a flag provided by sigaction api called SA_NOCLDSTOP.

	ACTUALLY IN THIS CASE WE ARE ACHIVED BY:
				see if a change in child state is occured then IT PASSES SIGCHLD to parent.
				so we are registering a signal handler for SIGCHLD, so if a SIGCHLD is recived then we are invoking a function cleanin_bySig() since we already blocked the 18,19 signals.
				so we are clearing the resouces only when if and only if SIGTERM is passed to child.
	note: pass all these 3 signals to child process only, by a using "kill" command in next-tab..
	`````	and see "ps -el".
	
	

********************************************************************************************************************************/
