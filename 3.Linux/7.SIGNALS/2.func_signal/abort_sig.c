//abort signal can be generated by kill..

#include<stdio.h>
#include<signal.h>

main(){
	
int i=0;

while(1){

	printf("%d \n",i);
	
	if(i==10) kill(getpid(),SIGABRT);
		
	i++;

	}

}
