#include<stdio.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>

main(){
getchar();
int fd=open("./text.c",O_RDWR);perror("open");
getchar();
char buff[25];
strcpy(buff,"learning LINUX"); perror("strcpy");

char *wptr=mmap(NULL,strlen(buff),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);perror("mmap");
getchar();
int i=0;
/*while(1){
if(i==strlen(buff)) break;
wptr[i++]='V';
}*/
strcpy(wptr,buff);perror("strcpy");
munmap(wptr,strlen(buff));perror("munmap");
getchar();
close(fd);perror("close");
}
