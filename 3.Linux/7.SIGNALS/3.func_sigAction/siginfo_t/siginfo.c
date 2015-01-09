/*
	In this prog our requirement is to pass some data to signalHandler function in this case SIGHAND funtion..
		using signal api we cannt achive it, since "signal api" doesnt provide such functionalities.. But
	by using "sigaction api" we can achive it by creating an instance of "siginfo_t"
				the member we used for this is in siginfo_t struct is:
				     1)  See it in siginfo_t of sigaction:  sigval_t si_value;    // Signal value
					its used for reading a sent data in the siganal handler..
					we are sent data by using "sigevent" api; In this api also we are having same number
				     2)  Sigval_t is a unioun "defined as sigval in man 7 sigevent"

	In this program i'm going to use following api, see those man pages
		man sigaction : for reading in the signal Handler function using "siginfo_t"; sa_flags = SA_SIGINFO  (must)
		man sigevent : for writing what values to be passed
		man sigqueue :  its also for writing only
		
		In sigevent ,sigqueue there will be an union object
				union sigval {                 // Data passed with notification 
	           			int sival_int;         // Integer value 
        	   			void *sival_ptr;       // Pointer value
       					};
		=====>	See the above thing is union so we cant use two elements at a time, since union the sizeof(biggest_member)			is taken and that is only used for data storage, so in union we can access only one member at a time..
			if u access 2 members(like update) the latest is stored..
		=====>  But in structures each member is associated with its own memory, but here(union) only one memory is used 			that is the biggest(largest) member in size. So if u use like:
							int k =123;
							sival_int = k;
							sival_ptr = &k;
					in this above scenario in the memory of union 1st k value is stored and then its 						updated to &k.. so in mem location only &k wil be there.. 
                                                        int k =123;
                                                        sival_ptr = &k;
                                                        sival_int = k;
					in this scenario in the memory of union 1st address of k is stored and then its updated to 					k value.. so in mem location only k value wil be there.. 
*/

//see the prog: "ven@VEN-LINUX:~/venky/Linux/IPC/1.msgQ/2.possix_impl/6.event_notify$ vi 2.event_1.c" for furether details

#include<stdio.h>
#include<signal.h>
#include<string.h>

void SIGHAND(int signo,siginfo_t *info,void *arg){

	printf("caught signal %d (%s)\n",signo,strsignal(signo));
	printf("passed value: %d\n",info->si_value.sival_int);  //if u use only 1st member
	//printf("passed obj addr: %p\n",(info->si_value.sival_ptr));  //if u pass ptr to object ie., if u use only 2nd member

	
}

void regSIG(int sig){

	struct sigaction act;
	bzero(&act,sizeof(act));  //its also like "memset" function but in memset function we can set any ascii value, but here its only zero;
	act.sa_sigaction = SIGHAND;
	act.sa_flags = SA_SIGINFO;   // (must and shud becoz we hav to read data in the sigHand using this info only)
	sigaction(sig,&act,NULL);

}

main(){


/******	using sigqueue api *********/  // see man sigqueue
	union sigval value;
	value.sival_int = 54321;
	regSIG(SIGUSR1);
	sigqueue(getpid(),SIGUSR1,value); //it automatically sends the signal to the pid provided along that data also passed

/************************************/
/***** using sigevent api **********/  //see man 7 sigevent
	
//	union sigval val;   we cant define union like this, so we just create an instance of "sigevent" automatically this union instance aloso created..
//	val.sival_int = 5321;  wrong method.. 

/*	struct sigevent eve;
	eve.sigev_notify = SIGEV_SIGNAL;
	eve.sigev_signo = SIGUSR1;
	eve.sigev_value.sival_int = 12345;
	//(mq_notify) we must use this to achieve this through "sigevent". see above mentioned program


	sleep(1);
	kill(getpid(),SIGUSR1); //or use raise(SIGUSR1);
*/
}
