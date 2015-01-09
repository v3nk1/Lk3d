//we have to give the pid of the proces here, next one ie., kill1.c is simpled coz of using command line arguments.

#include<stdio.h>
#include <sys/types.h> 
#include <signal.h>

main(){
	
	int i=0;

	while(1){ 
		
		i++;

		if(!(i==9||i==19)) kill( ,i);  // see the current executable pid in "ps -Af" as pass it as first argument.

		if(i==31) break;
		}
}
