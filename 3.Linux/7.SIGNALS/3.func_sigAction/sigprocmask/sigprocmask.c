//demostate and use possible functions to implement sigprocmask to block signals SIGINT,SIGQUIT,SIGALRM;

#include<stdio.h>
#include<signal.h>

void sig_check(sigset_t set){
	
	int i;
	for(i=1;i<=15;i++){
		if(sigismember(&set,i)==1) printf("Signal %d is in blocked set\n",i);
		else printf("signal %d is not in blocked set\n",i);
		}
}

main(){

	sigset_t set;
	sigemptyset(&set);
	
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGQUIT);
	sigaddset(&set,SIGALRM);
	
	sig_check(set);

	sigprocmask(SIG_BLOCK,&set,NULL);

	while(1);

}

/********************************************************************************************************************************
NOTES:
``````	 Using it we are, registering 3 signals for blocking through "sigaddset" API and then checking those are in set or not, by "sigismember" API and blocking them by "sigprocmask" by passing 

1st argument as: SIG_BLOCK,

2nd: sigset_t instance holding to be blocked signals.

3rd: NULL, if u dont want to read the previous set values. if u want to read then create an instance of sigset_t and passit as         reference of 3rd argument notice that it is outparm.

*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!/

