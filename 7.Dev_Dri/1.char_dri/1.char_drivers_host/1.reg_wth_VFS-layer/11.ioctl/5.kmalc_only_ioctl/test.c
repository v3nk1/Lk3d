
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#include"ioctl_H.h"

main(){

	rdwr_t red;

	int fd1,fd2;
	char buf[11],kbuf[100];
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

	memset(tbuf,'\0',sizeof(tbuf));
	memset(buf,'*',sizeof(buf));

	rdwr_t wr_obj = {
			.buf = buf,
			.size = sizeof(buf)-87987
			};

	while(1){
		if(ioctl(fd1,WR,&wr_obj)<0){
				perror("ioctl"); exit(123);
				}
		printf("%d\n",wr_obj.ret_val);
		if(wr_obj.ret_val<0) break;
		sleep(1);
		}

/*	memset(buf,'$',sizeof(buf));

			wr_obj.buf = buf;
			wr_obj.size = sizeof(buf);

	ioctl(fd1,WR,&wr_obj);
	
	lseek(fd1,0,SEEK_SET);
	red.buf = tbuf;	
	red.size = sizeof(tbuf);
	ioctl(fd1,RD,&red);

	write(1,red.buf,sizeof(red.buf));
*///	printf("%s\n",red.buf);
	
	close(fd1);
	close(fd2);
	
}
