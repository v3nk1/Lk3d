#include<fcntl.h>

main(){

	char buf[100]={};
	int fd=open("/sys/rtc_kobj/time",O_RDWR);
	perror("open");
	read(fd,buf,sizeof(buf));
	perror("read");
//	buf[10]='0';
//	write(fd,buf,sizeof(buf));
//	perror("write");
	printf("%s\n",buf);

}
