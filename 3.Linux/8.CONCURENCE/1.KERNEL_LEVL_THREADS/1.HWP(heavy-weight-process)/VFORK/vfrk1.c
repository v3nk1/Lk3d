#include<stdio.h>
#include<unistd.h>
 #include <sys/types.h>

main(){

	int i=10;
	switch(vfork()){
		
		case 0: printf("In child= %d\n",i);
			break;

		case -1:
			perror("vfork");
			break;	
		default:
			
			printf("In parent= %d\n",i);
			break;
		}
}
