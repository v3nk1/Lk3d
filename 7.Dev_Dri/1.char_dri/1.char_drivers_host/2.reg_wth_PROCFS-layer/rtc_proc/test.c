#include<stdio.h>
#include<fcntl.h>

main(){

	char time[]="time: 8:41:22";
	char date[]="date: 10/11/13";

	int fd1 = open("/proc/RTC/WR_RTC/write_time",O_RDWR);
	int fd2 = open("/proc/RTC/WR_RTC/write_date",O_RDWR);
	
	write(fd1,time,sizeof(time));
	write(fd2,date,sizeof(date));
	perror("write");
	
	close(fd1);
	close(fd2);
}
