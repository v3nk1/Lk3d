/*To demonstrate what if child is terminated before parent is terminated.

*/


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

main(){

	switch(fork()){

		case 0: 
			//sleep(5);  uncomment it if u want to see the process in ps -Af within 5 seconds.
			printf("child is terminated\n");
			abort();// to make the child to terminate..
			break;
			
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
			break;
		default:
			getchar();// to stop untill child termintes and to see the "ps -Af". since ZOMBIE process(defunc process) is created or not?
			printf("parent terminated\n");
			break;
		}

}

/********************************************************************************************************************************
NOTES:
``````	In this case, child will be there until parent terminates called "defunct state" or "ZOMBIE PROCESS".


********************************************************************************************************************************/
