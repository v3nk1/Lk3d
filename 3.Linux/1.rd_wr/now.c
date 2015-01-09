//Non interactive read/ write. ie., works like cp 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main(int argc,char *argv[]){
if(argc==3){
int fd_rd=open(argv[1],O_RDONLY);
int fd_wr=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0766);
char buff[25];
int p;
while(1){
//getchar();
//printf("%d\n",p);
	
	p=read(fd_rd,buff,sizeof(buff)); // to place /0 we hv to minus 1.
//	buff[p]='\0';   //it is necessary if u dnt give it gabage values result.
	
	if(p==0) break;
	write(fd_wr,buff,sizeof(buff));
//	printf("%s",buff);
	
}
close(fd_rd);close(fd_wr);
}
else printf("error\n");
}
lse pr