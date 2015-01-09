#define _GNU_SOURCE

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include<unistd.h>

main(int argc,char *argv[]){void *memptr;

	if(argc != 2){
		printf("Error: Usage: %s <file-name>\n",argv[0]);
		exit(133);
		}
	int fd;
	fd=open(argv[1],O_RDWR|O_DIRECT);perror("open");
	if(fd==-1) perror("open") , exit(1);
	//char buff[25]="qwertyuio";
	int SIZE=lseek(fd,0,SEEK_END); 
		/* 
		 * Here coz of lseek u moved the seek pointer to end of file 
		 * so.. u've to do set again to zero. Otherwise the read starts from end, 
		 * since seek pointer is there na??
		 */
	lseek(fd,0,SEEK_SET);
//	printf("%d\n",SIZE);
	
	/*TO MAKE THE SIZE AS MULTIPLE OF 512 WITH RESPECT TO SIZE OF FILE WE ARE READING*/
	if((float)SIZE/512 > (float)(SIZE/512)) SIZE=(SIZE/512+1)*512;
	else ;

	printf("%d\n",SIZE);

	if(posix_memalign(&memptr,512,SIZE))
			 /* 
			  * WHAT EVER SIZE U R PASSING HERE SHUD BE MULTIPLE OF 512, 
			  * if not it aint raise error but at reading time it shud raise 
			  * an error that invalid arguments. becoz in normal read no such 
			  * restriction but here we are using DIRECT I/O thus it suppress 
			  * the copying to I/O cache, so we must requset multiple of 512 size of data.
	 		  * In normal read(ie., w/o DIRECT I/O) we are read from I/O cache so u 
			  * can requset any num of bytes, not need to multiple of 512.
			  */
	perror("posix_memalign"),exit(321);

	int r=read (fd,memptr,SIZE);
	//see above posix_memalign comments..
	if(r==-1) perror("read"),exit(2);

close(fd);

	printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Content of the file!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n");
	/*we are writing to stdout ie., its work like printf */
	write(1,memptr,SIZE);
	printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  End of the file  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n");

}
