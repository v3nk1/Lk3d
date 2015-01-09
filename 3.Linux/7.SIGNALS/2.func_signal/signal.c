//w.a.p such that when you press ctrl+c cpu invoke your function instead of default action(termination). 

#include<stdio.h>
#include<signal.h>

void sig_hand(int signo){
	
	printf("signal handler for: %d\n",signo);
	getchar();  // here it is given to see our output. otherwise its an infinite loop na.. it so speedly executes printf;
		
	}

main(){

	//signal(SIGINT,sig_hand); or USE BELLOW ONE.
			
	signal(2,sig_hand);//for registering your function for sig_2(ie., ctrl+c). so after this registration is successfull when u press     ctrl+c it goes to invoke our function sig_hand. That is you are registering your function to ctrl+c., so it leaves default action and invokes your function. 

	perror("signal"); getchar(); //for checking the success status.

	while(1) printf("test\n");
	}
