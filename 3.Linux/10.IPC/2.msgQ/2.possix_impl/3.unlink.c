//unlink a existed possix msgQ; compile with -lrt

#include <stdio.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mqueue.h>

main(int argc , char *argv[]){

	if(argc == 2){
	
		if((*argv[1])!= '/') printf("Invalid name: naming convention '/<name>'\n"),exit(1);

		if(mq_unlink(argv[1])==-1) perror("mq_unlink"),exit(1);
	}
	
	else printf("Missing argument:\nUsage: sudo ./a.out /<name>\n");

}
