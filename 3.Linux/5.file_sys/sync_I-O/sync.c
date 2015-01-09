#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

main(int argc, char *argv[]){
int fd;
//getchar(); placed here to observe proc in /proc
fd=open(argv[1],O_SYNC|O_CREAT|O_TRUNC|O_RDWR,0766);
if(!fd) perror("fopen"),exit(1);

//getchar();
char *str="i'm doing file I/O 's\n";
int p=write(fd,str,strlen(str));
if(p==-1) perror("write"),exit(2);
//getchar();
close(fd);
//getchar();
}
