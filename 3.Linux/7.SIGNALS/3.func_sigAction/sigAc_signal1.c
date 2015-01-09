// SIGACTION works as SIGNAL FUNCTION  using second member of it...

#include<stdio.h>
#include<signal.h>

void sig_hand(int signo,siginfo_t *temp,void *p){ // see the signatures..

	printf("registered signal%d\n",signo);

}

main(){
	struct sigaction obj;
		
	obj.sa_sigaction = sig_hand;
	
	sigaction(SIGINT, &obj, NULL);
	sigaction(SIGCHLD, &obj, NULL);  // pass it from new-tab pkill -SIGCHLD a.out

	while(1);
	
}
