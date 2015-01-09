//to read/change the flags of a opened files: using api fcntl();

#define _GNU_SOURCE	// its for O_DIRECT, if u dont define it compilation error wil occur..
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

void read_flags(int flags){


	printf("O_RDONLY flag is: %s\n",!(flags & O_RDONLY)? "ON" : "OFF");  //since RDONLY flag value = 0,so if on ! den always  false, means "OFF" will print.  see text book linux prog interface pageno:93
	printf("O_WRONLY flag is: %s\n",(flags & O_WRONLY)? "ON" : "OFF");
	printf("O_RDWR   flag is: %s\n",(flags & O_RDWR)  ? "ON" : "OFF");
	printf("O_APPEND flag is: %s\n",(flags & O_APPEND)? "ON" : "OFF");
	printf("O_CREAT  flag is: %s\n",(flags & O_CREAT) ? "ON" : "OFF");//Doesnt support by fcntl();
	printf("O_TRUNC  flag is: %s\n",(flags & O_TRUNC) ? "ON" : "OFF");//Doesnt support by fcntl();
	printf("O_ASYNC flag is : %s\n",(flags & O_ASYNC)?  "ON" : "OFF");
	printf("O_DIRECT flag is: %s\n",(flags & O_DIRECT)? "ON" : "OFF");
	
	printf("\n");

}

main(){

	printf("O_RDONLY=%d\nO_WRONLY=%d\nO_RDWR=%d\n\n",O_RDONLY,O_WRONLY,O_RDWR);//printing flag values of open

	int fd = open("./test_18",O_RDONLY|O_WRONLY|O_ASYNC); //here O_DIRECT CAUSES PROBLEM, Identified by "perror".
	/*char temp[]="/tmp/venXXXXXX";
	int fd = mkstemp(temp);getchar();*/
	int flags; 
	
			printf("In parent:\n");
			flags = fcntl(fd,F_GETFL); 
			
			if(flags==-1) perror("fcntl"),exit(100);
			read_flags(flags);

	switch(fork()){

		case 0:	
			printf("In child:\n");
			flags = fcntl(fd,F_GETFL);
			if(flags==-1) perror("fcntl"),exit(200);
			read_flags(flags);

			flags |= O_APPEND;
			fcntl(fd,F_SETFL,flags); //See using it we can modify O_DIRECT,O_APPEND,O_NONBLOCK,O_NOATIME,O_ASYNC only.
			perror("fcntl");
			
			printf("changes made in child:\n");	
			flags = fcntl(fd,F_GETFL);
			if(flags==-1) perror("fcntl"),exit(300);
			read_flags(flags);
			break;

		default:
			//lets checkout changes made in child is effectd parent or not?? ans: no effect., 1 doesnt effect other.
			printf("Any changes in parent??: NO\n");
			flags = fcntl(fd,F_GETFL);
			if(flags==-1) perror("fcntl"),exit(400);
			read_flags(flags);
			break;
	}

}

/********************************************************************************************************************************
NOTES:
`````` Changes made in child to the fd of the opened file doesnt effect the parent and vicevesa..

*********************************************************************************************************************************/
