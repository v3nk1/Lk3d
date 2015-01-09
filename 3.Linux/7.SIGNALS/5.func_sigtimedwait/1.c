//To understand how sigwaitinfo works..

#include<stdio.h>
#include<signal.h>

main(){

	sigset_t set;
	siginfo_t info;//if u want details of the signal.
	
	struct timespec timeout;
	timeout.tv_sec = 10;	

	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGQUIT);	
	
	sigtimedwait(&set,&info,&timeout); //it will suspend the execution thread until u press ether one of the signal populated in the set.

	printf("caught signal %d\n",info.si_signo); //it gives info of pressed signal, if it is in the set passed in sigwaitinfo.
			//but for interrupt(sig:2) it wont work.. since it will terminate the process at that particular instance.
}
