//pass the getted pid from the process as command line argument followed by ./kill1,ie., by running 1st ./sig on other tab..

#include<stdio.h>
#include <sys/types.h> 
#include <signal.h>

main(int argc, char *argv[]){
	
if(argc==2){

	int i=0;

	while(1){ 
		
		i++;

		if(!(i==9||i==19)) kill(atoi(argv[1]),i);  // see the current executable pid in "ps -Af" as pass it as first argument.

		if(i==31) break;
		}

	}
else printf("invalid use of command line arguments\n"),exit(1);
}
