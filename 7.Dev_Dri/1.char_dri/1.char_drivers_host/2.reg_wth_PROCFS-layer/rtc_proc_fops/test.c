#include<stdio.h>
#include<fcntl.h>

main(){

	char wrtime[]="time: 10:27:22";
	char rdtime[100];
	char wrdate[]="date: 21/12/13";
	char rddate[100];

	int fd1 = open("/proc/RTC/rw_time",O_RDWR);
	int fd2 = open("/proc/RTC/rw_date",O_RDWR);
	
//	read(fd1,time,sizeof(time));
	//perror("write");
	write(fd1,wrtime,sizeof(wrtime));
	write(1,rdtime,read(fd1,rdtime,sizeof(rdtime)));
	write(1,rddate,read(fd2,rddate,sizeof(rddate)));
//	write(fd2,date,sizeof(date));
//	perror("write");
	
	close(fd1);
	close(fd2);
}
