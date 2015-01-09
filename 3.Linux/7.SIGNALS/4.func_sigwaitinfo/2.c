//To understand how sigwaitinfo works..

#include<stdio.h>
#include<signal.h>

main(){

	sigset_t set;
	siginfo_t info; // if u want details(information) of the signal.
	
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGQUIT);	
	
	sigprocmask(SIG_BLOCK,&set,NULL); //if unfortunately u press ctrl+c before waitng of sigwaitinfo() it wont responds.To make that we are using sigprocmask and blocked those signals. actually without this also works correctly.
	
	printf("sleep for 2 seconds:\n");
	sleep(3);

	printf("sigwaitinfo() waiting for signal:\n");
	sigwaitinfo(&set,&info);//it will suspend the execution thread until u press ether one of the signal populated in the set.

	printf("caught signal %d\n",info.si_signo); //but for interrupt(sig:2) it wont work.. since it will terminate the process at that particular instance.

}
