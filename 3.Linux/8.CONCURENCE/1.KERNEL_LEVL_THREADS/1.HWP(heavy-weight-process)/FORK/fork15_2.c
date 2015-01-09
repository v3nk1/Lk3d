// to check what will be happend when u open a file seperately in child and parent respectively.
		//then no update of ofset wil result result. offset updation is result only when u open a file commonly ie., above fork.

#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

main(){

	char buff[2];
	
	switch(fork()){

		case 0: 
			printf("child:\n");	

			int fd=open("./123",O_RDONLY);
			int rd=read(fd,buff,sizeof(buff));
			write(1,buff,rd);
			
			printf("off = %lu\n",lseek(fd,0,SEEK_CUR));
			break;

		default:
			printf("parent:\n");
			wait(NULL);

			fd=open("./123",O_RDONLY);
			rd=read(fd,buff,sizeof(buff));
			write(1,buff,rd);

			printf("off = %lu\n",lseek(fd,0,SEEK_CUR));
			
			break;
		}

			
}
