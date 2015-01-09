#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

main(){

	int fd;
	char buf[100],kbuf[100];
	char tbuf[200];
	fd = open("/dev/misc_API",O_RDWR);
	perror("open");

	memset(buf,'A',sizeof(buf));
	printf("wret: %d\n",write(fd,buf,sizeof(buf)));
	memset(buf,'B',sizeof(buf));
	printf("wret: %d\n",write(fd,buf,sizeof(buf)));
	printf("%d\n",lseek(fd,0,SEEK_CUR));

	perror("write");
	lseek(fd,0,SEEK_SET);
	read(fd,tbuf,sizeof(tbuf));
	perror("read");

/*	memset(buf,'\0',sizeof(buf));
	memset(buf,'B',sizeof(buf));
	write(fd,buf,sizeof(buf));
	perror("write");
	read(fd,tbuf,sizeof(tbuf));
	perror("read");

*/	write(1,tbuf,sizeof(tbuf));
	perror("write");
//	write(1,tbuf,sizeof(tbuf));

	close(fd);
	
}
