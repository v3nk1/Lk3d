#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define LED_ON 	"0"
#define LED_OFF "1"

main(){

	int fd1;

	fd1 = open("/dev/led_dev",O_RDWR);
	if(fd1<0){
		perror("open");
		return;
		}
	
	write(fd1,LED_ON,1);

//	getchar();
	close(fd1);
	
}
