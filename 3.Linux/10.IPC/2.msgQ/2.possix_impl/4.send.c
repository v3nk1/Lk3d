//to send msg to already created possix msgQ..

#include<stdio.h>
#include <fcntl.h>       
#include <sys/stat.h> 
#include <mqueue.h>

main(){

	mqd_t mid;
	mid = mq_open("/create",O_WRONLY/*|O_CREAT|O_EXCL,0664,NULL*/);

	if(mid == -1) perror("mq_open");
	
	char str[] = "i'm legend";

	if(mq_send(mid,str,strlen(str),11)==-1) perror("mq_send");
	
}
