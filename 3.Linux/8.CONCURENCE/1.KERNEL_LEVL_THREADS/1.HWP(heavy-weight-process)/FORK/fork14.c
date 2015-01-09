/*
	Prog to check wheather the opened files in parent are inhereted to the child process or not?
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

main(){

	int fd = open("./test_13",O_CREAT|O_RDWR,0664);

	switch(fork()){

		case 0:
			printf("child:\n");
			write(fd,"testing fork",12);
			break;
		default:
			printf("parent:\n");
			break;
	}	

}

// see fds of parent and child: in /proc/fd..
