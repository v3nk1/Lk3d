//FIRST CREATE A PIPE BY "MKFIFO <PIPE_NAME>" IN SHELL PROMPT

#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

main(){

int fd=open("./pipe",O_RDONLY);
char buff[2500];

while(1){
	int k=read(fd,buff,sizeof(buff));
	if(k==0) break;  //its very importent to come out of loop, if no break then even ./write is terminated by ^C its executes printf infinitely..
	printf("readed data:\n");
	printf("````````````\n");
	write(1,buff,k);
	printf("______________________________________________________________________________________________________\n");
	}
}
