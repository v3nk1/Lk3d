/* its not known that when child executes or when parent will executes.. its purely up to the cpu schedular

	it wil be in random time, ./a.out > log and see the log
*/

//To separate child and parent actions we will go with return values of fork(). Using it we can do that. checking return values by switch or if-else its up to u.

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>  //for exit();

main(){

	pid_t pid = fork();
	
	switch(pid){
		
		case 0: 
			 while(1) printf("its in child context\n");
			 break;

		case -1: 
			 perror("fork");
			 exit(1);
		default:
			 while(1) printf("its in parent context\n");
			 
			 break;
		}
}




/*

HERE ALSO IT IS NOT KNOWN THAT HOW MUCH TIME CHILD EXECUTES AND HOW MUCH TIME PARENT WILL EXECUTE. ITS PURELY DEPENDABLE TO THE   TIME GIVEN BY SCHEDULER. SINCE SCHEDULAR IS THE ONE WHICH WILL GIVE TIME SLICE FOR CPU, (upto wht time which prog will execute).

*/
