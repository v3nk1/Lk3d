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
printf("pid: %d\n",getpid());
getchar();
while(1){
//getchar();
//printf("%d\n",p);
	
	p=read(fd_rd,buff,sizeof(buff));// printf("%d-",rd);// to place /0 we hv to minus 1.
//	buff[p]='\0';   //it is necessary if u dnt give it gabage values result. \0 appended only when u r printing the data coz we are using %s there.

	if(p==0) break;
//	write(fd_wr,buff,sizeof(buff)); error some garbage values wil print.
//	write(fd_wr,buff,strlen(buff)); error some garbage values wil print becoz strlen calculates no of char upto \0 but here we didnt append any /0 na? so garbage values will there.


	write(fd_wr,buff,p);//printf("%d\n",wr); //this will going to rock correctly becoz we just write how many char read func readed.
//	printf("%s",buff);
	
}
close(fd_rd);close(fd_wr);
}
else printf("see the command line arguments"),exit(1);
}
