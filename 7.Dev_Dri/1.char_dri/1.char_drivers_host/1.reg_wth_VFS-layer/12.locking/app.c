#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

main(){

	int fd;
	fd=open("/dev/testdev",O_RDWR);
	read(fd,NULL,0);
	printf("application terminated normally\n");
}
