#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <signal.h>

int fd,oflags;

//void hand(int no){
void hand(int no,siginfo_t *info,void *arg){
		//info->si_fd is not working
	char buf[100]={};
	printf("Initiating read..\n");
	read(fd,buf,sizeof(buf));
	perror("read");
	printf("Read: %s\n",buf);
}

main(){

	char buf[100];
	if((fd=open("/dev/vdev123",O_RDWR))==-1)//O_RDWR|O_ASYNC, no signal intimation 
			perror("open");

	fcntl(fd,F_SETOWN,getpid());	//Must otherwise no SIGIO intimation
	oflags=fcntl(fd,F_GETFL);
	oflags|=O_ASYNC;		// OR oflags|=FASYNC;
	fcntl(fd,F_SETFL,oflags);
	
//	signal(SIGIO,hand);

	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_sigaction=hand;
	act.sa_flags=SA_SIGINFO;
	sigaction(SIGIO,&act,NULL);

	while(1);//Engage in other work

}
