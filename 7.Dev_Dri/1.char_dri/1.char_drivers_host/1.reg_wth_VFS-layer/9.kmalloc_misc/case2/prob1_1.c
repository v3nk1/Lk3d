#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

main(){

	int fd;
	char buf[1024];
	fd = open("/dev/misc_API",O_RDWR);
	if(fd<0) perror("open"),exit(1);
	read(fd,buf,sizeof(buf));
	write(1,buf,sizeof(buf));

	close(fd);
	
}
