//compile with "cc <name> -lpthread -lrt"
//create new shared memory

#include"headers.h"

main(int argc,char *argv[]){

if(argc == 2){
	
	if(*argv[1] == '/'){

	int fd;
	if((fd = shm_open(argv[1],O_RDWR|O_CREAT,0664)) == -1) perror("shm_open"); //Name must be start with "/", it must be in root directory.. thats why / must be there..
	
	if(ftruncate(fd,getpagesize())) perror("ftruncate");
	void *offset = mmap(NULL,getpagesize(),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);


	}
	
	else printf("Invalid arguments\nUsage: %s </name>\n",argv[0]);

	}

else printf("Invalid arguments\nUsage: %s </name>\n",argv[0]);

}


//you can see the created shared memory "ls /dev/shm";
