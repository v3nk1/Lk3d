#define _GNU_SOURCE
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

main(int argc,char *argv[]){
	void *memptr;
	int fd= open(argv[1],O_DIRECT|O_CREAT|O_RDWR,0766);
	if(fd==-1) perror("open"),exit(1);
	posix_memalign(&memptr,512,4096);
	read(0,memptr,4096);//reading input from user.. like scanf
	write(fd,memptr,4096);
close(fd);
}
