#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

main(){

	int fd = open("./file.txt",O_RDWR);

	unsigned long tmp,pos = lseek(fd,0,SEEK_END);
	write(fd,"END",3);
	
	printf("pos: %d\n",pos);
	tmp=lseek(fd,pos-3,SEEK_SET);
	printf("%lu\n",tmp);
	
//	write(fd," ",1);

}
