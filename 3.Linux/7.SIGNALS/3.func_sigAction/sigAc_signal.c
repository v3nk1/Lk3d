// SIGACTION works as SIGNAL FUNCTION... using first member..

#include<stdio.h>
#include<signal.h>

void sig_hand(int signo){ //see the signatures of this and next programm..

	printf("registered signal%d\n",signo);

}

main(){

	struct sigaction obj;
//	memset(&obj, 0 ,sizeof(obj));   used to fill all that memory by 0's. if u got any segmentation fault use it..
		
	obj.sa_handler = sig_hand;
	
	sigaction(SIGINT,&obj,NULL);
	sigaction(SIGQUIT,&obj,NULL); //no need to declare a separate object and separate handler..

	while(1);
	
}
