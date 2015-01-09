/*TO OVERCOME ZOMBIE STATE, parent shoud collect the exit state of child and inform to kernel.
	COLLECTING THE EXIT STATE OF CHILD: 1) synchronous cleaner method. using 2 API'S

										a) wait();  in fork8.c

										b) waitpid(); in fork9.c
*/


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<string.h>
#include<signal.h>


void check(int stat){

//	if(WIFEXITED(stat)) printf("exit normally:%d\n",WIFEXITED(stat));
//	else printf("exited forcebly\n"); // u uncomment abort(); in child and see this mesg will displayed.
	
	if(WIFEXITED(stat)) 
		printf("%d\n",WEXITSTATUS(stat));

	else if(WIFSIGNALED(stat)) printf("signal:%d (%s)\n",WTERMSIG(stat),strsignal(WTERMSIG(stat)));
	else if(WIFSTOPPED(stat)) printf("signal:%d (%s)\n",WSTOPSIG(stat),strsignal(WSTOPSIG(stat)));
	else if(WIFCONTINUED(stat)) printf("child is resumed by SIGCONT\n");
}	

main(){

	int stat; /* if u declare stat in parent context(ie., in default: child cant acess it.) if u want to access u must declare it above fork() only. but in open(), close() calls its different,
						u can access a file opened in parent context (in default:) from child.
*/
	switch(fork()){

		case 0: /*CHILD CONTEXT*/
		//	check(stat);
			printf("child is terminated\n");
			
			//abort(); // if u place it, u are forcibly terminates the child by SIGABRT signal.
			break;
			
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
			break;
		default: /*PARENT CONTEXT*/
			printf("enters into parent context\n");
			waitpid(-1,&stat,0); /*IT MUST BE HERE, IF U PUT AFTER GETCHAR() IT WORKS BUT U CANNOT SEE. */
			check(stat);
			getchar();// to stop untill child termintes and to see the "ps -Af". since ZOMBIE process(defunc process) is created or not?
			printf("parent terminated\n");
			break;
		}

}

/***********************************************************************************************************
NOTES:
``````	If u give getpid() API in parent context ie.,in "default case:" it will give parent pid, 
	If u give getpid() API in child context ie., in "case 0:"it will give child pid.

*************************************************************************************************************/
