#include<stdio.h>
#include<signal.h>

void sig_hand(int num){
	
	printf("alarm worked\n");
	
/* USE ANY OF THE FOLLOWING KILL ONLY */

	//kill(getpid(),SIGTERM);// i want to pass signal from curret process by alarm..
	//kill(getpid(),SIGINT); 
	//kill(getpid(),SIGKILL);
	//kill(getpid(),SIGQUIT);
	kill(getpid(),6);
	
	//alarm(2); // if you want to execute alarm periodically then..
}

main(){
	
	signal(SIGALRM,sig_hand);
	alarm(3);
	while(1); //its an infinite loop..

	}


/********************************************************************************************************************************

NOTES:
******
	See here the thing is alarm works for any signal num passed in signal function. But it simply comes out of loop and prints
just a message that ALARM CLOCK.
	No application defined function invoked here if u pass other than SIGALRM macro as first argument of signal function.

=> 	See one more importent point about alarm is, its a 1 shot exectuion, ie., it executes once and removed from kernel and 
     resumed the task what it leaved before alarm signal arrived.
	
	if you want to execute it periodically see above..

********************************************************************************************************************************/
