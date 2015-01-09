#include<stdio.h>
#include<sys/time.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>

void func(int signo){

	printf("Caught signal %s:",strsignal(signo));
	fflush(stdout);system("date");
}

main(){

	struct itimerval tm;
	bzero(&tm,sizeof(tm));
/*Interval*/
	tm.it_interval.tv_sec=1;
//	tm.it_interval.tv_usec=10;

/*Initialization(triggering) timer*/
	tm.it_value.tv_sec=1/*10*/;
		/*
		 * Specify 10 value here will initialise the timer after 10sec.
		 * triggers the timer after completion of 10sec.
		 */
//	tm.it_value.tv_usec=1;

	signal(SIGALRM,func);
	setitimer(ITIMER_REAL,&tm,NULL);
		/*
		 * As a timer progresses, it counts down from the initial value (it_value) toward 0.
		   When the timer reaches 0, the corresponding signal is sent to the process, and
		   then, if the interval (it_interval) is nonzero, the timer value (it_value) is reloaded,
		   and counting down toward 0 recommences.
		 * ITIMER_REAL
			Create a timer that counts down in real (i.e., wall clock) time. When the
			timer expires, a SIGALRM signal is generated for the process.
		 */
	printf("Timer registerd: ");
	fflush(stdout);system("date");

//	getchar();
	while(1);

}
