
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#include"ioctl_H.h"

main(){

	int fd1,fd2;
	char buf[100],kbuf[100];
	char tbuf[200];

	fd2 = open("/dev/old1",O_RDWR);
	if(fd2<0){
		perror("open");
		return;
		}
	fd1 = open("/dev/old0",O_RDWR);
	if(fd1<0){
		perror("open");
		return;
		}

/*	memset(buf,'A',sizeof(buf));
	write(fd1,buf,sizeof(buf));
	
	memset(buf,'*',sizeof(buf));
        write(fd2,buf,sizeof(buf));
	
	memset(buf,'B',sizeof(buf));
	write(fd1,buf,sizeof(buf));
	
	memset(buf,'!',sizeof(buf));
	write(fd2,buf,sizeof(buf));

	lseek(fd1,0,SEEK_SET);
	lseek(fd2,0,SEEK_SET);
*/	
//	int t;
	getchar();
	printf("%d\n",ioctl(fd1,FLUSH_BUF));
	perror("ioctl");
	ioctl(fd2,FLUSH_BUF);
//	printf("size: %d\n",t);
		
	read(fd1,tbuf,sizeof(tbuf));
	write(1,tbuf,sizeof(tbuf));
	write(1,"\n",1);
/*
	read(fd2,tbuf,sizeof(tbuf));
	write(1,tbuf,sizeof(tbuf));
	write(1,"\n",1);
*/
	close(fd1);
	close(fd2);
	
}
