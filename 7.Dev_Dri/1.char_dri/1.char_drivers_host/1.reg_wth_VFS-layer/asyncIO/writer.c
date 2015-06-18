#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

main(){

	int fd,oflags;
	char buf[100]={"piontlessMsg"};
	printf("%s\n",buf);
	if((fd=open("/dev/vdev123",O_RDWR))==-1) 
			perror("open");

	write(fd,buf,sizeof(buf));
	getchar();
}
