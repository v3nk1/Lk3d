#include<stdio.h>
#include<unistd.h>

main(){

	printf("BEFORE FORK\n");

	printf("see (PARENT) process by ps -Af in other shell\n");
	getchar();// up to here in "ps -Af" only one a.out will be there(PARENT).

	fork(); // after fork there is another a.out is created called child process.
		
	printf("again see child process by ps -Af in other shell\n"); //this statement executes 2 times becoz once in child/parent and other in parent/child.. we dont know which will execute first it is purely depens on schedular.
	getchar();

}
