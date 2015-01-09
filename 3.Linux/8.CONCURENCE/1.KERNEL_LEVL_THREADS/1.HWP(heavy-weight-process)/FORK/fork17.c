/*To check wheather the blocked signals are inhereted by the child process from its parent process.

*/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>

void blck_SIGINT(void){

	sigset_t blck;
	sigemptyset(&blck);
	
	sigaddset(&blck,SIGINT);
	sigprocmask(SIG_BLOCK,&blck,NULL);

}

main(){

	blck_SIGINT();  //to see the difference comment it and run; uncomment it and run; and in both cases pass SIGINT to child.

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
````` Here u must pass SIGINT to child process only, by seeing pid of child in ps -Af.  (or)
				by pkill -2 a.out (since in this only 1 a.out will be there, parent terminated na..)
      If u send it by key board its defaultly ment to parent processes. means u are sending signal to parent process.

      Here in this program parent terminates before child. so _init becomes parent to that child.
*********************************************************************************************************************************/
