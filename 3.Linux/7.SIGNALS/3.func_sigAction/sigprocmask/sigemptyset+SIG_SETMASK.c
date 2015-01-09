//Here in this scenario we will see how to block the signals while a sigHandler is in execution. by using "sigprocmask" API and the key use of SIG_SETMASK in emptying the sigempty set in kernel space.

#include<stdio.h>
#include<string.h>
#include<signal.h>

void checkin_set(sigset_t set){

	int i;
	for(i=1;i<=14;i++){
		if(sigismember(&set,i)) printf("signal %d is in set\n",i);
		else printf("signal %d is not in set\n",i);
		}

	printf("\n");
}

void sig_int(int signo){

	printf("caught signal %d (%s)\n",signo,strsignal(signo));

}

main(){

	sigset_t set;
	sigemptyset(&set);

	sigaddset(&set,SIGINT);// 1.
	sigaddset(&set,SIGQUIT);// 2. 
					//so 1 & 2 are also reside in user space, since "set" is resides in userspace only.
	

	sigprocmask(SIG_BLOCK /*| SIG_SETMASK*/,&set,NULL);//HERE WE ARE REGISTERING THOSE SIGNALS TO KERNAL since kernel is the one which is responsible for signal response routines., ie., somewhere in kernel space this information is stored.
	printf("1st sleep\n");

//	alarm(5);// it will execute, becoz we ain't blocked it yet.// becoz of default behaviour of evry signal after it reminds alarm it'll terminate the process. if u dnt want that behaviour then define ur own handler for alarm and register it by using sigaction/signal API.
	
	sleep(15);    //here if u press ctrl+c and ctrl+\ it will block those signals but BLOCK always keeps those in a que remember that. after completion of sleep it will exetute those que.

//	checkin_set(set);// it also prints user space information.
	
	sigemptyset(&set); //see its actually emptying the set but in USER_SPACE.
//	checkin_set(set);  //so it shows(PRINTS) list that there is no signals SIGINT,SIGQUIT; yes ofcource it true, the above fuction clears those in USER_SPACE.
		
	sigaddset(&set,SIGALRM); //so by this it will append SIGALRM signal to the set if u dont use SIG_SETMASK followed by SIG_BLOCK.
	struct sigaction act;
	act.sa_handler=sig_int;
	sigaction(2,&act,NULL);

	act.sa_handler=sig_int;
	sigaction(SIGQUIT,&act,NULL);

	sigprocmask(SIG_BLOCK | SIG_SETMASK,&set,NULL);
	printf("2nd sleep\n");
	alarm(5);// it wnt be execute, becoz its being blocked by kernel.

//	checkin_set(set);

	sleep(15);
	
}
