//w.a.p such that when you press ctrl+c cpu invoke your function instead of default action(termination) only once, and after goes to its default action.

#include<stdio.h>
#include<signal.h>

void sig_hand(int signo){
	
	printf("signal handler for: %d\n",signo);
	getchar();
	signal(2,SIG_DFL); // to go back to its default action.	
	}

main(){

	signal(2,sig_hand); //for registering your function for sig_2(ie., ctrl+c). so after this registration is successfull when u press     ctrl+c it goes to invoke our function sig_hand. That is you are registering your function to ctrl+c., so it leaves default action and invokes your function. 
	while(1) printf("test\n");
}
