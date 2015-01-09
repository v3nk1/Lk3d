#include<fcntl.h>

main(){

	char buf[100]={};
	int fd=open("/sys/rtc_kobj/time",O_RDWR);
	read(fd,buf,sizeof(buf));
	printf("%s\n",buf);

}
