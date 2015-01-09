//observe the outputs for both defer.c and nodefer.c

#define _GNU_SOURCE
//#define sign(a) #a                        //============> 1
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>


void sig_hand(int signo,siginfo_t *info,void *p){
//void sig_hand(int signo){
	static int tmp;	
	tmp++;
	printf("signal passed:%d\n",info->si_signo);
	//printf("this signal-%d means %s called by %d times\n",signo,sign(SIGINT),tmp);   //===========> 1
	sleep(5);
	printf("this signal-%d means %s called by %d times\n",signo,strsignal(signo),tmp);

}

main(){

	struct sigaction obj;
	memset(&obj,0,sizeof(obj)); // mem set here compulsary. without this its like DEFER ONLY,EVEN IF U PUT SA_NODEFER...
	obj.sa_sigaction = sig_hand;

	obj.sa_flags = SA_SIGINFO;

	sigaction(SIGINT,&obj,NULL);
		
	while(1) sleep(1),printf("temporory programm\n");

}
