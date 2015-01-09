//Run its executable in one tab

#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

main(){

	int fd;
	char buf[1024];
	fd = open("/dev/misc_API",O_RDWR);
	int i;
	memset(buf,'*',sizeof(buf));
	for(i=0;i<1024;i++){
	write(fd,buf+i,1);
	sleep(1);
	}
	write(1,buf,sizeof(buf));

	close(fd);
	
}
