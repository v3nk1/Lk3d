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
			wait(NULL); /*IT MUST BE HERE, IF U PUT AFTER GETCHAR() IT WORKS BUT U CANNOT SEE. */
			getchar();// to stop untill child termintes and to see the "ps -Af". since ZOMBIE process(defunc process) is created or not?
			printf("parent terminated\n");
			break;
		}

}

/*****************************************************************************************************************
NOTES:
``````	To use waitpid() API, see fork9.c


******************************************************************************************************************/
