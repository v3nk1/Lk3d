//system is used to execute shell command

#include<stdio.h>
#include<stdlib.h>

main(){

	char commd[100];

while(1){
	printf("ven@prompt: ");
	scanf(" %[^\n]",commd);
	if(!strcmp(commd,"exit")) break;
	if(system(commd)==-1) perror("system");
	}

}
