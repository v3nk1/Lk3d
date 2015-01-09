#include<stdio.h>
#include<fcntl.h>

main(){

	char time[]="time: 8:41:22";
	char date[]="date: 21/12/13";

	int fd1 = open("/proc/RTC/rw_time",O_RDWR);
	int fd2 = open("/proc/RTC/rw_date",O_RDWR);
	
	//write(fd1,time,sizeof(time));perror("write");
	//write(fd2,date,sizeof(date));perror("write");
	read(fd1,time,sizeof(time));
	read(fd2,date,sizeof(date));
	
	printf("%s\n%s\n",time,date);

	close(fd1);
	close(fd2);
}
