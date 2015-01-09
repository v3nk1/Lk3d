//to receive all msg from the specifed msgQ..

#include<stdio.h>
#include <fcntl.h>       
#include <sys/stat.h> 
#include <mqueue.h>

main(){

	mqd_t mid;
	mid = mq_open("/create",O_RDONLY);
	if(mid == -1) perror("mq_open");

	struct mq_attr attr;

	attr.mq_flags = O_NONBLOCK;
//	attr.mq_msgsize = 6; even u set it, compiler will ignore it

	mq_setattr(mid,&attr,NULL);
	mq_getattr(mid,&attr);

	printf("currnet num of msgs in the msgQ: %d\n",attr.mq_curmsgs);
	
	char *str = (char *)malloc(attr.mq_msgsize+1);

	printf("size = %ld\n",attr.mq_msgsize);
	
	int i=0;
	while(i++<attr.mq_curmsgs){ //to read all msgs in the present opened msgQ
//	unsigned int k=11;
	if(mq_receive(mid,str,attr.mq_msgsize+1,NULL)==-1) perror("mq_receive"),exit(1);

	printf("received msg: %s\n",str);
	}
}
