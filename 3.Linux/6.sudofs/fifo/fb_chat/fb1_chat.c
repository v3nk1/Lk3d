#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

main(){

	mkfifo("./pipe1",0664);
	mkfifo("./pipe2",0664);
	int fd1_wr = open("./pipe1",O_WRONLY);
	int fd2_rd = open("./pipe2",O_RDONLY);

	fd_set rd_fd,wr_fd;
	FD_SET(fd2_rd,&rd_fd);
	FD_SET(fd1_wr,&wr_fd);
	struct timeval time;
	time.tv_sec = 10;
	
	char buff[1000];
	while(1){
	select(5,&rd_fd,&wr_fd,NULL,&time);
	if(FD_ISSET(fd2_rd,&rd_fd)){
		printf("reading data:");
		 int rd=read(fd2_rd,buff,sizeof(buff));
		 write(1,buff,rd);	
		}
	else	{
		printf("writing data:");
		int rd = read(0,buff,sizeof(buff));
		write(fd1_wr,buff,rd);
		}
	}
}
