//to notify an event by signal using possix msgQ..
		//here we declared mdes as globally in followed programs this will be removed by passing it to signalHandler..

	//we are getting a mesg by running the executables created in the previous dir to this dir..
		//first create a que by running executable of 1.create.c and  run this in other(2nd) tab, and send.c 1st tab, observe 2nd tab..

//We can see this notification registration in "cat/mnt/create" after mount "mqueue" file sys on /mnt

#include <stdio.h>
#include <mqueue.h>

#include <signal.h> //for strsignal()
#include <string.h>

#include<stdlib.h>//for exit()

int mdes;//(its not int, its a mq_t type)   //mdes means msgQ descriptor.  in next program this will be declared as local to main(),so we'll pass "mdes" to sigHandler and read it in signalHand with the help of siginfo_t in the sigaction api..

void rec_mesg(void){
	
	char buf[100];
	
	struct mq_attr attr;
	mq_getattr(mdes,&attr);

	int size = attr.mq_msgsize +1;
	
	int rcv = mq_receive(mdes,buf,size,NULL); //i'm not interested inn the readed msg priority val(so i passed NULL)
	if(rcv == -1) perror("mq_receive"),exit(3);

	/*the problem with printf here is printf invoked last ie., after system call write, since 1st system call are invoked and then API's*/
//	printf("Recieved msg: ");
	write(1,"Received msg: ",14);
	write(1,buf,rcv); //writing the received msg onto "STDOUT"

	printf("\n");

}

void sigHand(int signo){

	printf("caught signal: %d (%s) for event notification\n",signo,strsignal(signo));
	rec_mesg();
	
}

void reg_sig(){

	struct sigevent eve;

	eve.sigev_notify = SIGEV_SIGNAL;
	eve.sigev_signo =  SIGUSR1;

	signal(SIGUSR1,sigHand);//here we are registering signal using signal api so we cannt pass any value to signal Handler function.. if u want to pass use sigaction api..
	
	if(mq_notify(mdes,&eve) == -1) perror("mq_notify"),exit(2);

}

main(){

	mdes = mq_open("/create",O_CREAT|O_RDWR,0664,NULL);
	if(mdes == -1) perror("mq_open"),exit(1);
	
	reg_sig();
 
	while(1); //main thread is doing its job; as and when the event signal(a new msg is delivered into an empty queue by other process) occured then it will halt the current process and read the msg and print it onto stdout.. and continues it halted job.
}
