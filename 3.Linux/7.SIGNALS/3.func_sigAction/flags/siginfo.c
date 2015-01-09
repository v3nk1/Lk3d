#include<stdio.h>
#include<signal.h>

void signalHandler(int signo,siginfo_t *info,void *p){

	printf("signal Handler:%d\n",info->si_signo);

}

main(){

	struct sigaction obj;
	//siginfo_t info; 	//no need to create its instance
	obj.sa_sigaction = signalHandler;
	obj.sa_flags=SA_SIGINFO;
	sigaction(SIGINT,&obj,NULL);
	while(1);

}
