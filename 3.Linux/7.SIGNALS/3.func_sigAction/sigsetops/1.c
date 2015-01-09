//TO DEMONSTRATE HOW TO USE "SIGSETOPS" FUNCTIONS..

#include<stdio.h>
#include<signal.h>

main(){

	int i;

	struct sigaction obj;

	sigset_t temp;  // sigset_t is a stucture type variable predeclared in signal.h, it is required here to use sigsetops functions.
	
	sigemptyset(& temp);// its used to clear garbage values in declared temp,becoz its a local variable,all local variables initial state is garbage.

	sigfillset(&temp); //i dont knw up to how much it'll set, but upto very long. except 32 and 33.

	// sigaddset() / sigdelset() adds or delete 1 by 1;
	
	for(i=1;i<=100;i++){
	
		if(sigismember(&temp,i)/*==1*/) printf("signal no %d is in set\n",i);
					//sigismember checks and returns 1 if the particular signal is in temp; else returns 0. 

		else printf("signal no %d is not in set\n",i);
	}
}
