#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>

main(){

	int fd;
	if((fd=open("/dev/my_chr_dev",O_RDWR)) == -1 ) perror("open");

	if(read(fd,"RD-SUCCESS",0)==-1) perror("read");
	if(write(fd,"WR-SUCCESS",0)) perror("write");

}
