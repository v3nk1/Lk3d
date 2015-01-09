//Non interactive read/ write. ie., works like cat
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main(int argc,char *argv[]){
if(argc==2){
int fd=open(argv[1],O_RDONLY);
char buff[25];  //here if u give buff[4096] then no garbage results, no need to put \0 if only our file size less than 4096 bytes.
int p;
while(1){
//getchar();
//printf("%d\n",p);
	
	p=read(fd,buff,sizeof(buff)-1); // to place /0 we hv to minus 1.
	buff[p]='\0';   //it is necessary if u dnt give it gabage values result.
	if(p==0) break;
	printf("%s",buff);
	
}
close(fd);
}
else printf("error\n");
}
