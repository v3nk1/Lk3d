#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>

main(int argc,char *argv[]){

	int fd=open(argv[1],O_WRONLY|O_CREAT,0660);
	write(fd,argv[2],strlen(argv[2]));
	//write(fd,'\0',1);
	close(fd);

	fd=open(argv[1],O_RDONLY,0660);
	char buf[5];
	//lseek(fd,1,SEEK_CUR);
	lseek(fd,0,SEEK_SET);int rd=0;
	while(1){

		int p=read(fd,buf,sizeof(buf)-1);rd+=p;
		if(rd==strlen(argv[2])) 
			break;//printf("%d %d\n",p,rd);
		buf[p]='\0';
		//getchar();
		printf("%s",buf);//write(stdout,ch,strlen(ch));
		}
	printf("\n");

	close(fd);
}
