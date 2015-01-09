//class room exersize: to check the opened file above fork() ie., in parent, is accessible in child or not., actually(in here case) it works like cat wraper.


#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

main(){

	int fd=open("./123.c",O_RDWR);
	char buff[100];
	
	switch(fork()){
		case 0: while(1){
			
			int rd=read(fd,buff,sizeof(buff));
			if (rd==0) break;
			write(1,buff,rd);
			
			}
			break;
		default:
			wait(NULL);
			break;
		}

			
}
