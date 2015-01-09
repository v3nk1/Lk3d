
#include<stdio.h>
#include<sys/uio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

main(){

struct iovec iov[2];
getchar();

int fd=open("./test_wr.c",O_RDONLY);perror("open");
getchar();

char buff1[15];  //here we have to declare 2 buffers seperately and give their addresses to respective buffers;
char buff2[9];

iov[0].iov_base=buff1;
iov[0].iov_len=sizeof(buff1);


iov[1].iov_base=buff2;
iov[1].iov_len=sizeof(buff2);
//buff[3].iov_len=9;

readv(fd,iov,2);
perror("readv");
getchar();


/*    NO NEED OF THIS BELLOW SHIT-STUFF INSTEAD USE "WRITEV" TO VERIFY THAT UR BUFFERS ARE FILLED AS U REQUSETED OR NOT   */
	
//SINCE PRINTF CAUSES SOME PROBLEMS LIKE %S,FOR THIS WE HAVE 2 GIVE THE BASE ADDESS OF BUFF(if it's string) IN FORM OF (CHAR*),BUT WHO WILL APPEND /0...
//````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
/*
printf("%s",(char *)iov[0].iov_base);    //type-cast to (char *) to suppress error,since %s used for (char*) but in pre-defined structure void pointer;
perror("printf");


printf("%s\n",(char *)iov[1].iov_base);
perror("printf");*/

//````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````

writev(1,iov,2);
printf("\n");
}
