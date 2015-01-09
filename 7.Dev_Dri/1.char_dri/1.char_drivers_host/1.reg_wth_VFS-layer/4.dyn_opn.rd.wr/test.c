#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

main(){

	int fd;
	if((fd=open("/dev/vdev123",O_RDWR))==-1) 
			perror("open");

	char buf[100];
	if(read(fd,buf,sizeof(buf))<0)
			perror("read");
	printf("red frm dev: %s\n",buf);


	if(write(fd,"SUCCESS_WR",0)<0)
			perror("write");
	
	close(fd);
	
	if(write(fd,"SUCCESS_WR",0)<0)
			perror("write");

}
