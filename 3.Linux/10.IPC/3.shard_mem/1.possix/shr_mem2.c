//compile with "cc <name> -lpthread -lrt"
//delete(unlink or remove) a created shared memory

#include"headers.h"

main(int argc,char *argv[]){

if(argc == 2){
	
	if(*argv[1] == '/'){

	if((shm_unlink(argv[1])) == -1) perror("shm_unlink");
	
	}
	
	else printf("Invalid arguments\nUsage: <executable> </name>\n");

	}

else printf("Invalid arguments\nUsage: <executable> </name>\n");

}


//you can see the created shared memory "ls /dev/shm";
