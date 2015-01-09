#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
main(int argc,char *argv[]){
if(argc<=1) printf("command not found\n");
else{ 
	int p;
	p=mkdir(argv[1],S_IRWXU|S_IRGRP|S_IWGRP|S_IROTH);
	if(p==-1) perror("mkdir"),exit(1);
	}	

}
