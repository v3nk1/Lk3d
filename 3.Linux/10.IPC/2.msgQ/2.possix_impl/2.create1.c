//open an exited possix msgQ;

#include <stdio.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mqueue.h>

main(){

	mqd_t mid;
	if(mid = mq_open("/create",O_RDWR|O_NONBLOCK)==-1) perror("mq_open"),exit(1);
	printf("mid = %u\n",mid);
}
