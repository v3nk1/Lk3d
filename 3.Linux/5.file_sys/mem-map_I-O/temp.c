#include<stdio.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>

main(){
int fd=open("./rd_text.c",O_RDWR);perror("open");
int fd1=open("./wr_text.c",O_RDWR);perror("open");
//char buff[25];

#define strlen(buff) 10 

char *wptr=mmap(NULL,strlen(buff),PROT_READ|PROT_WRITE,MAP_SHARED,fd1,0);perror("mmap");
char *rptr=mmap(NULL,strlen(buff),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);perror("mmap");
int i=0;
for(;i<strlen(buff);i++)
	wptr[i]=rptr[i];
munmap(wptr,strlen(buff));perror("munmap");
munmap(rptr,strlen(buff));perror("munmap");
close(fd);perror("close");
close(fd1);perror("close");
}
                                        
