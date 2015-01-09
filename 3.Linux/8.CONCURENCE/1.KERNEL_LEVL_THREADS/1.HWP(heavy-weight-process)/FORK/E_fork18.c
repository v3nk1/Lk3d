//to read/change the flags of a opened files: using api fcntl();

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

void read_flags(int flags){


	printf("O_RDONLY flag is: %s\n",(flags & O_RDONLY)? "ON" : "OFF");
	printf("O_WRONLY flag is: %s\n",(flags & O_WRONLY)? "ON" : "OFF");
	printf("O_RDWR   flag is: %s\n",(flags & O_RDWR)  ? "ON" : "OFF");
	printf("O_APPEND flag is: %s\n",(flags & O_APPEND)? "ON" : "OFF");
	printf("O_CREAT  flag is: %s\n",(flags & O_CREAT) ? "ON" : "OFF");
	printf("O_TRUNC  flag is: %s\n",(flags & O_TRUNC) ? "ON" : "OFF");
	
	printf("\n");

}

main(){

	int fd = open("./test_18",O_RDONLY);
	
	int flags = fcntl(fd,F_GETFL);
	
			printf("In parent:\n");
			flags = fcntl(fd,F_GETFL);
			read_flags(flags);

	switch(fork()){

		case 0:	
			printf("In child:\n");
			flags = fcntl(fd,F_GETFL);
			read_flags(flags);
			flags |= O_CREAT;
			fcntl(fd,F_SETFL,flags);	
			break;

		default:
			
			printf("Changed in parent:\n");
			flags = fcntl(fd,F_GETFL);
			read_flags(flags);
			break;
	}

}
