//w.a.p that will print the address space of its own

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>

main(){

	pid_t pid;
	pid = getpid();
	printf("%u\n",pid);
	char Path[123];
	char buf[100];

	/*
	 * Actually in /proc there is an directory which holds the current renning process called "self"
	 * Or, using "sprintf" we can achive it..
	 */

	sprintf(Path,"/proc/%d/maps",pid);
//	int rd,fd = open("/proc/self/maps",O_RDONLY);
	int rd,fd = open(Path,O_RDONLY);
		if(fd<0) perror("open"),exit(1);
	
	while(1){
		rd = read(fd,buf,sizeof(buf));
		if(!rd) break;
		write(1,buf,rd);
		}
}
