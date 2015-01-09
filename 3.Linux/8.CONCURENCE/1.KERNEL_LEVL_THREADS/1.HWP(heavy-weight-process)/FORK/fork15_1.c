//read/write calls demonstation: offset of opened file  will be updated here.(if and only if u opened file above fork());\
				if u opened in switch casess individual behaviour will be seen means no updating of offset there.


#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

main(){

	int fd = open("./test_13",O_RDONLY);
	
	char buff[2];

	switch(fork()){
		
		case 0://child
			printf("In child: \n");
			printf("starting offset = %lu\n",lseek(fd,0,SEEK_CUR)); //here lseek is like ftell();
			read(fd,buff,2);// instead read just place "pread".(change argument as defined in man pread.)
			write(1,"read: ",6);
			write(1,buff,2);
			printf("\n");
			printf("ending offset = %lu\n",lseek(fd,0,SEEK_CUR));
			close(fd);//even if u close same output.
			break;
			
		case -1:
			perror("fork");
			break;

		default://parent          1st parent wil execute, so make sure that u perform read/write here,check lseek in child
			printf("In parent: \n");
			printf("starting offset = %lu\n",lseek(fd,0,SEEK_CUR));
			read(fd,buff,2);// instead read just place "pread".(change argument as defined in man pread.)
			write(1,"read: ",6);
			write(1,buff,2);
			printf("\n");
			printf("ending offset = %lu\n",lseek(fd,0,SEEK_CUR));
			break;
	}	

}




/********************************************************************************************************************************NNOTES:
``````	TO AVOID THIS WE USE pread, pwrite API'S. // or u can use lseek to set the offset to required position
	In this no update of offset takes place.

*********************************************************************************************************************************/
