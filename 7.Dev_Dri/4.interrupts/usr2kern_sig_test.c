#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

void sighand(int no,siginfo_t *info,void *arg){

	printf("%s: %s\n",__func__,strsignal(no));

}

int main(){

	int fd;
	fd = open("/dev/u2k",O_RDONLY);
	if(fd<0){
		perror("open");
		exit(1);
		}
	struct sigaction act={};
	act.sa_sigaction=sighand;
	act.sa_flags=SA_SIGINFO;
	sigaction(SIGRTMAX,&act,NULL);
	while(1);
	
	return 0;
}
