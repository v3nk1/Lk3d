/*
 * Try to see the asembly for with and without volatile
 * cc volatile.c -m32 -O2 -save-temps	-> For uncomment 1
 * -> uncomment 2
   cc volatile.c -m32 -O2 -save-temps -DVOLATILE=volatile
   cc volatile.c -m32 -O2 -save-temps -DVOLATILE=  ;
 */
#include <string.h>
#include <stdio.h>
#include <signal.h>

/*1*/
//volatile
/*2*/
//VOLATILE
int quit;

void hand(int no){
	
	quit=1;
	printf("%s Caught signal\n",__func__);

}

main(){

#if 1   
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_handler=hand;
	act.sa_flags=SA_RESTART;
	sigaction(SIGINT,&act,NULL);
#else
    signal(SIGINT,hand);
#endif
    while(!quit);
		// without volatile !quit replaced by 1(true).

}
