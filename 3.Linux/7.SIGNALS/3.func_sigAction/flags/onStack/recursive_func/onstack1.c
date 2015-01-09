//it's a non-executable statement. since above function is recursive.#define _GNU_SOURCE
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>


void sig_handler(int signo){

        printf("caught signal:%d (%s)\n",signo,strsignal(signo));
	exit(1);   // without this is going to print infinite times..
	//abort();
}

void stack_overflow(int i){

	printf("recursive func executes: %d times\n",i++);
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
	obj.sa_handler = sig_handler;

	//alloc_altstack(); 
	
	sigaction(SIGSEGV,&obj,NULL);
	perror("sigaction");
	stack_overflow(1);
	
	printf("end of main\n");//it's a non-executable statement. since above function is recursive.

}
