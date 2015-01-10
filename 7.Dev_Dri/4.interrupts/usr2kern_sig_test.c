/*
 * Test application for sending signal form 
   kernel to user land.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

void sighand(int no){

	printf("%s: %s\n",__func__,strsignal(no));

}

int main(){

	int fd;
	fd = open("/dev/u2k",O_RDONLY);
	if(fd<0){
		perror("open");
		exit(1);
		}
	signal(SIGRTMAX,sighand);
	while(1);
	
	return 0;
}
