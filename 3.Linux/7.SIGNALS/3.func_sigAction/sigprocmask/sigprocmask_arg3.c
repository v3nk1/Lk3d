//By this program we are demonstrating the 3rd argument usage in sigprocmask API.
	//its only used if u are interested in reading the previous status of the signals.

#include<stdio.h>
#include<signal.h>

void check_stat(sigset_t stat){

	int i;
	for(i=1;i<=15;i++){
		if(sigismember(&stat,i)) printf("signal %d is in blocked list\n",i);
		else printf("signal %d is not in blocked list\n",i);
	}
}

main(){

	sigset_t set,stat;
	sigemptyset(&set);
	sigemptyset(&stat);
	
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGALRM);
	
	sigprocmask(SIG_BLOCK,&set,NULL);  //first of we have to block the signals. since in bellow statment you are passing 3rd argument, so that is an out-param. In that the previous values are updated.

	sigprocmask(SIG_BLOCK,NULL,&stat);// here in stat the previous signal states are populated.

	check_stat(stat);

}
