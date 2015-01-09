//to see how many signals are registering..

#include<stdio.h>
#include<signal.h>

void sig_hand(int signum){

	printf("sig_%d is registered\n",signum);
	getchar();

	}

main(){
	
	printf("pid of current process: %u\n",getpid());
	getchar();
	int i=0;
	while(i++<31) {
		if(signal(i,sig_hand)==SIG_ERR) printf("ERROR %d\n",i),getchar();
		else signal(i,sig_hand), printf("SUCCESS %d\n",i);
		}
	while(1) printf("testing all signals\n");

	}
