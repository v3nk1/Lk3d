//To understand how d old_act(ie., 3rd argument of sigaction) works, since its is same here in sigprocmask but named as oldset..
	//NOTE: HERE NOTE THAT ABOVE 2 ARE OUTPARMS.,

#include<stdio.h>
#include<signal.h>
#include<string.h>


void check_state(struct sigaction *state){

	if(state -> sa_handler == SIG_DFL ) printf("signal is doing default operation\n");
 	else{
		if(state -> sa_handler == SIG_IGN) printf("signal is IGNORED\n");
        	else printf("signal is doing app signal handler\n");
		}
		
}

void sigHandler(int no){
	
	printf("caught signal %d (%s)\n",no,strsignal(no));

}

main(){

	struct sigaction curnt_act,old_act;
	memset(&curnt_act,0,sizeof(curnt_act));
	memset(&old_act,0,sizeof(old_act));
	
	curnt_act.sa_handler = SIG_IGN;
	sigaction (SIGINT,&curnt_act,&old_act);
	printf("old state: "); check_state(&old_act); //it prints previous(default) operation
	printf("new state: "); check_state(&curnt_act); //it prints IGNORED
	sleep(10);
	printf("\n");
	//getchar(); or use getchar();
	
	curnt_act.sa_handler = sigHandler;
	sigaction (SIGINT,&curnt_act,&old_act);
	printf("old state: "); check_state(&old_act);//it prints previous(SIG_IGN) operation
	printf("new state: "); check_state(&curnt_act);//it prints present(app defined sigHandler)
	sleep(10);
	printf("\n");
	//getchar(); or use getchar();

	curnt_act.sa_handler = SIG_DFL;
	sigaction (SIGINT,&curnt_act,&old_act);
	printf("old state: "); check_state(&old_act);//it prints previous(app defined sigHandler)
	printf("new state: "); check_state(&curnt_act);//it prints present(default) operation
	sleep(10);
	printf("\n");
	//getchar(); or use getchar();

}
