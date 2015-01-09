#include<stdio.h>
#include<sys/uio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>

main(){
char *str1="veda solutions";
char *str2=" LINUX PRO\n";

int fd=open("./test_wr.c",O_CREAT|O_TRUNC|O_RDWR,0766);

struct iovec buff[2];

buff[0].iov_base=str1;
buff[0].iov_len=strlen(str1);

buff[1].iov_base=str2;
buff[1].iov_len=strlen(str2);

//writev(1,buff,2);// prints on run screen itself like printf==========> fd's: stdin=0,stdout=1,stderr=2;

writev(fd,buff,2);
close(fd);
}
