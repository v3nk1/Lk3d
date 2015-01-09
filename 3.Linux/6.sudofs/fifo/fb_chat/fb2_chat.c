#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

main(){

	int fd1_rd = open("./pipe1",O_RDONLY);
	int fd2_wr = open("./pipe2",O_WRONLY);

	fd_set rd_fd,wr_fd;
	FD_SET(fd1_rd,&rd_fd);
	FD_SET(fd2_wr,&wr_fd);
	struct timeval time;
	time.tv_sec = 1;
	
	char buff[1000];
	while(1){
	select(5,&rd_fd,&wr_fd,NULL,&time);
	if(FD_ISSET(fd1_rd,&rd_fd)){
			printf("reading data:");
			int rd=read(fd1_rd,buff,sizeof(buff));
			write(1,buff,rd);
			}
	else{
		printf("writing data:");
		int rd = read(0,buff,sizeof(buff));
		write(fd2_wr,buff,rd);
		}
	
	}
}
