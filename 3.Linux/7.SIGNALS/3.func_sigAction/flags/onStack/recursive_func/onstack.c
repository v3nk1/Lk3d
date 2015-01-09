#include<stdio.h>
#include<signal.h>

void stack_overflow(int i){

	printf("%d\n",i++);	
	char temp[100000];
	stack_overflow(i);

}


void sig_handler(int signo,siginfo_t *info,void *p){
	
	printf("no more space in stak\n");

}

main(){
	
	struct sigaction obj;
	obj.sa_sigaction = sig_handler;
	sigaction(SIGSEGV,&obj,NULL);
	stack_overflow(1);
	printf("end of main\n");//it's a non-executable statement. since above function is recursive.

}


/***********************************************************************************************************

NOTES:
^^^^^^
	See here in this case application defined signal handler will not executed because there'll be no enough space to store this signal handler after recursive function. so default SIGQUIT is thrown by cpu.
	if you want to execute your signal handler the only one possibility is ALLOCTE SEPERATE STACK FOR SIGNAL HANDLER.

**********************************************************************************************************/
