//FIRST CREATE A PIPE BY "MKFIFO <PIPE_NAME>" IN SHELL PROMPT

#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

main(){

int fd = open("./pipe",O_RDONLY);
int fd1 = open("./pipe",O_WRONLY);

char buff[2500];
struct timeval time;
time.tv_sec=5;

fd_set rdfd;
fd_set wrfd;

FD_SET(fd,&rdfd);
FD_SET(fd1,&wrfd);


while(1){
	
int x=select(3,&rdfd,&wrfd,NULL,&time);
	
	if(FD_ISSET(fd,&rdfd)){
		int k = read(fd, buff, sizeof(buff));
		printf("readed data:\n");
		printf("````````````\n");
		write(1, buff, k);
		printf("______________________________________________________________________________________________________\n");
		}
	else/*(FD_ISSET(fd1,&wrfd))*/{
		printf("write data :\n");
		printf("````````````\n");
        	int k=read(0, buff, sizeof(buff));
		write(fd1,buff,k);
        	printf("______________________________________________________________________________________________________\n");
		}
	}

}
