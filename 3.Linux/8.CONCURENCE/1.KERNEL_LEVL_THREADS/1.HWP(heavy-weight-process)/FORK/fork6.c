/*To demonstrate what if parent is terminated before child is terminated.

*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

main(){

	switch(fork()){

		case 0: 
			getchar();  // to see the ps -Af and after parent terminates. we hav to wait na??
			printf("child is terminated\n");
			break;

		case -1:
			perror("fork");
			exit(EXIT_FAILURE); //macro defined in stdlib.h
			break;
		default:
			sleep(5);
			printf("sleep completed\n");
			break;
		}

}

/*********************************************************************************************************************************
NOTES:
``````	1)  In such cases ofcourse child will run since it hav its own resources(PCB,ADDRESS SPACE).
	  but in ps -Af the ppid coloumn if it have the terminated parent pid then it will be a bug, so in such cases the "_INIT" 	    will become its parent untill it terminates normally.
	
	2) _init is the one which is responcible for all process(ie., grand parent), to deallocte the memory allocated for a 		    paricular child process parent has to report the "exit state" of the child to kernel then kernel will clear that memory, 	      but here parent is terminated itself before child, so to deallocation mem and some reasons "_init" will take that 		resposible and become as a parent to that child.

IN ps -Af :(see init) right-most, init has no parent ppid=0, and its pid=1 since 1st process when u boot the system.
```````````
UID        PID  PPID  C STIME TTY          TIME CMD
root         1     0  0 13:01 ?        00:00:00 /sbin/init


*********************************************************************************************************************************/
