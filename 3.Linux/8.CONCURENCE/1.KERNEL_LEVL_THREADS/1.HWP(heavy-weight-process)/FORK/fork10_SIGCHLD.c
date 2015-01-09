/*TO CHECK WHEATHER THE "SIGCHLD" IS SENT BY THE CHILD PROCESS WHEN IT STOPS,CONT,TERM..??

		To check that in a newtab by kill signal generate them.. like as 
							kill -SIGSTOP/SIGCONT/SIGTERM <pid>
							kill -19/18/2 <pid>			
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>


void cleanin_bySig(int signo){ // user defined signal handler for SIGCHLD.

	wait(NULL); //if u want status pass an integer as argument.
	printf("signal: %d (%s) is recieved\n",signo,strsignal(signo));
	
}

void disp_sig(int signo){

	printf("signal: %d (%s) is recieved\n",signo,strsignal(signo));

}

void reg_SIGCHLD(){

	struct sigaction act;
	memset(&act,0,sizeof(act));
	
	act.sa_handler = cleanin_bySig;
	act.sa_flags = SA_RESTART|SA_NODEFER;
	sigaction(SIGCHLD,&act,NULL);

}

main(){
	
	
	switch(fork()){

		case 0: /*CHILD CONTEXT*/
			
			printf("child context\n");
			signal(SIGSTOP,disp_sig); //it wont executes, compiler simply ignores it.
			signal(SIGCONT,disp_sig);
			signal(SIGINT,disp_sig);
			getchar(); //see ps -el
			//sleep(10);
			printf("child is terminated\n");
			break;
			
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
			break;

		default: /*PARENT CONTEXT*/

			printf("enters into parent context\n");

			reg_SIGCHLD();

			//cleanin_bySig(0); it not be here, no need of it here, BLUNDER.

			getchar();// to stop untill child termintes and to see the "ps -Af". since ZOMBIE process(defunc process) is created or not?
			printf("parent terminated\n");
			break;
		}

}

/********************************************************************************************************************************
NOTES:
``````	its more clear in "ps -el" than "ps -Af"
	In ps -el the 2st column state of processes will be there, "S = SUSPEND",
				 				   "T = TERMINATION", 

********************************************************************************************************************************/
