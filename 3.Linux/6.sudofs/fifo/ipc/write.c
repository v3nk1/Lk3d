//FIRST CREATE A PIPE BY "MKFIFO <PIPE_NAME>" IN SHELL PROMPT



#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

main(){

	int fd=open("./pipe",O_WRONLY);
	printf("fifo opened\n");
	char buff[2500];
	while(1){
		printf("enter data:\n");
		int k=read(0,buff,sizeof(buff));
		printf("_________________________________________________________________________________________________\n");
		write(fd,buff,k);
		}
}
