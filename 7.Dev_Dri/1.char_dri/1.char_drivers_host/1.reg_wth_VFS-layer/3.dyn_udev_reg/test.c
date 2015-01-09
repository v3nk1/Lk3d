#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

main(){

	int fd;
	if((fd=open("/dev/vdev123",O_RDWR))==-1) 
			perror("open");

	if(read(fd,"SUCCESS_RD",0)<0)
			perror("read");

	if(write(fd,"SUCCESS_WR",0)<0)
			perror("write");
	
	close(fd);
	
	if(write(fd,"SUCCESS_WR",0)<0)
			perror("write");

}
