/*To check wheather the signal handlers are inhereted by the child process from its parent process.

*/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>

void print_sig(int signo){

	printf("signal: %d (%s) is recieved\n",signo,strsignal(signo));
	exit(1); //it makes to execute handler 1 time only. after 1 time forceble exit will happens.
}

void reg_SIGINT(void){

	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_handler = print_sig;

	sigaction(SIGINT,&act,NULL);

}

main(){

	reg_SIGINT();

	switch(fork()){

		case 0: 
			printf("child:\n");
			while(1) printf("point less message\n"); //if u giv odd loop without a message in child, we are unable to  know whethere the process is in execution or terminated.
			break;
		default:
			printf("parent:\n");
			break;
	}
}


/********************************************************************************************************************************
NOTE:
````` Here u must pass SIGINT to child process only, by seeing pid of child in ps -Af.
      If u send it by key board its defaultly ment to parent processes. means u are sending signal to parent process.

      Here in this program parent terminates before child. so _init becomes parent to that child.
*********************************************************************************************************************************/
