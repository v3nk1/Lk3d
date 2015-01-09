//IN THIS APPROACH OUR AIM IS TO BLOCK "SIGSEGV" SIGNAL SEND BY CPU WHEN STACK OVERFLOW OCCURS, BY USING "SIGPROCMASK" FUNCTION.

//error: its not possible to block..

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>


/*void sig_handler(int signo){

        printf("caught signal:%d (%s)\n",signo,strsignal(signo));
	exit(1);   // without this is going to print infinite times..
	//abort();
}
*/

void stack_overflow(int i){

	printf("rec func executes: %d times\n",i++);
	char temp[100000];
	stack_overflow(i);

}


	

void alloc_altstack(void){

	stack_t mem;
	mem.ss_sp = calloc(SIGSTKSZ,1); // u can use malloc also, but in calloc the intial values are set to zero..
	mem.ss_size = SIGSTKSZ;
	mem.ss_flags = 0;
	sigaltstack(&mem,NULL);
	perror("sigaltstack");

}

main(){
	
	struct sigaction obj;
	memset(&obj,0,sizeof(obj));

	alloc_altstack();

	obj.sa_flags = SA_ONSTACK;
	obj.sa_handler = SIG_IGN;
	//alloc_altstack();
//	sigaddset(&obj.sa_mask,SIGSEGV);
//	sigprocmask(SIG_IGN,&obj.sa_mask,NULL);
	//perror("sigprocmask");

	sigaction(SIGSEGV,&obj,NULL);
		
	//sigaction(SIGSEGV,&obj,NULL);
	//perror("sigaction");
	stack_overflow(1);
	
	printf("end of main\n");

}
