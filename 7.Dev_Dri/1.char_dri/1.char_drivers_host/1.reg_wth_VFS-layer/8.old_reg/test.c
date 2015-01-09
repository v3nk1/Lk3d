#include<stdio.h>
#include<fcntl.h>

main(){

	int fd;
	//if(open("/dev/oldDev0",O_RDWR)<0)
	if(open("/dev/oldDev1",O_RDWR)<0)
		perror("open");

}
