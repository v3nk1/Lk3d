/*TO DEMONSTRATE THE 3rd method of cleanup(collectin the exit state of child):
``````````````````````````````````````````````````````````````````````````````
						AUTO CLEANUP: achived by passing a flag SA_NOCLDWAIT provided by sigaction API,
*/


#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>

void _SIGCHLD(int signo){

	printf("signal:%d (%s) is recieved\n",signo,strsignal(signo));

}

void reg_SIGCHLD(){

	struct sigaction act;
	memset(&act,0,sizeof(act));
	
	act.sa_handler = _SIGCHLD; // or u can give here SIG_DFL also.
/*1*/	act.sa_flags = SA_NOCLDWAIT | SA_NOCLDSTOP | SA_RESTART; 
					//if u put SA_RESTART here then the process will come back and\
					waits in getchar() funtion, otherwise no waiting will be there entire\
					process will be terminated automatically if signal SIGCHLD occured. 

		//if u want here also block SIGSTOP,SIGCONT then pass SA_NOCLDSTOP flag also. it wont respond for signals 18,19 so that resouces will not be cleared for 19,18. resources will be cleared if and only if child is terminated by a signal SIGINT, or normal sequential termiation of child.
	
	sigaction(SIGCHLD,&act,NULL);

}

main(){

	switch(fork()){

		case 0: 
			printf("CHILD CONTEXT\n");
/*1*/			getchar(); //pass those three signals 18,19,2 by kill in next tab see the "ps -el"
			break;    // and obeserve defunc state in "ps -el" when commenting one of the flag at a time.

		case -1:
			perror("fork");
			break;

		default:
			reg_SIGCHLD();
			printf("PARENT CONTEXT\n");
			getchar();
			break;
	}

}
