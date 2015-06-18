/* 
   BLOCKING SIGNAL WHEN A SIGNAL HANDLER IS IN EXECUTION 
 		   ``````````````````````````````````````
   masking means blocking a signal with in the handler.
   means it will be queued until handler completed. 
 */

#include<stdio.h>
#include<signal.h>
#include<string.h>

void sigHandler(int no){

	printf("caught signal %d (%s)\n",no,strsignal(no));

	sleep(10);//here sleep is must and shud becoz to make it as above under lined heading..
	//getchar(); we can use get char also..
	
}

main(){

	struct sigaction obj;
	memset(&obj,0,sizeof(obj));

	sigemptyset(&obj.sa_mask);
	obj.sa_handler = sigHandler;

/* SO HERE WE ARE BLOCKING TWO SIGNALS WHILE A SIGNAL HANDLER IS IN EXECUTION*/
	sigaddset(&obj.sa_mask,SIGQUIT);  
		/* through this fuction we are pushing one by one signal 
		 * numbrs to mask(assume its like array) of type sigset_t 
		 * defined in signal.h header file. 
		 */
	sigaddset(&obj.sa_mask,SIGINT); // pushing SIGINT..


/******************************************************************************************************
ANOTHER WAY OF ABOVE 2 STATEMENTS IS:
`````````````````````````````````````
	1) Declare a object of type sigset_t, which is a predifined 
	   in signal.h header file, ie., we are just creating its instance.
	like: sigset_t mask;
	
	2) And use same sigaddset() func, but instead of 1st argument pass just &mask;
	
	like: sigaddset(&mask,SIGQUIT);

	3) After u complete adding signals what u want to block,
		assign "mask" to obj.sa_mask;
			
	like: obj.sa_mask = mask;
***************************************************************************************************/
	
	sigaction(SIGALRM,&obj,NULL);
	alarm(3); //alarm is must here or else u shud manually pass it by kill -14 < pid > in another tab.
	
	while(1);

}
