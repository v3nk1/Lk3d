#include<stdio.h>
#include"ioctl_header.h"
#include<fcntl.h>

main(){

	int year=0x14,date=0x11,mon=0x12;
	int hr,min,sec;
		
	int fd = open("/dev/rdrtc123",O_RDWR);

//	ioctl(fd,WR_DATE,date);
//	ioctl(fd,WR_YR,year);
//	ioctl(fd,WR_MON,mon);

	ioctl(fd,RD_DATE,&date);
	ioctl(fd,RD_YR,&year);
	ioctl(fd,RD_MON,&mon);
	
	ioctl(fd,RD_HOUR,&hr);
	ioctl(fd,RD_MIN,&min);
	ioctl(fd,RD_SEC,&sec);

	printf("%x/%x/20%x\n",date,mon,year);
	printf("%02x:%02x:%02x\n",hr,min,sec);

}
