/*To notify an event by signal using possix msgQ..
	Here i want to pass some data to signal handler such that i can use that data in signal hand function.. so achive this we must register signal handler with sigaction api only signal api is doesnt provide any such data passing tools..
		first see "/venky/Linux/7.SIGNALS/func_sigAction/siginfo_t$ vi siginfo.c"

*/

#include <stdio.h>
#include <mqueue.h>

#include <signal.h> //for strsignal()
#include <string.h>

#include<stdlib.h>//for exit()


void rec_mesg(void *ptr_mdes){
	
	int mdes = *(int *)ptr_mdes;
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


void sigHand(int signo,siginfo_t *info,void *arg){

	printf("caught signal: %d (%s) for event notification\n",signo,strsignal(signo));
/*1*/	printf("passed value to sigHand: %d\n",info->si_value.sival_int); 
		//here both above printf bellow printf will print same values becoz of union concept, in union all members are 		pointing to same address only..
/*2*/	printf("passed pointer: %d\n",info->si_value.sival_ptr);
/*2*/	rec_mesg(info->si_value.sival_ptr);
		
}

void data_passtosigHand(struct sigevent *p_eve,int intger,void *obj_p){
	
/*u can use only one of the bellow statements*/
/*1*/	//(p_eve -> sigev_value).sival_int = intger;
/*2*/	(p_eve -> sigev_value).sival_ptr = obj_p;

}

void reg_sig(int *mdes_p){

	static struct sigevent eve; //it must be globally declared
	eve.sigev_notify = SIGEV_SIGNAL;
	eve.sigev_signo =  SIGUSR1;

/*1*/	int intger = 54321;
/*2*/	void *obj_ptr = mdes_p;

	data_passtosigHand(&eve,intger,obj_ptr);

	struct sigaction act;
	bzero(&act,sizeof(act));

	act.sa_sigaction = sigHand;
	act.sa_flags = SA_SIGINFO;//must
	sigaction(SIGUSR1,&act,NULL);
	
	if(mq_notify(*mdes_p,&eve) == -1) perror("mq_notify"),exit(2);  //registering event notification functionality by invoking mq_notify..

}

main(){

	int mdes;   //mdes means msgQ descriptor
	mdes = mq_open("/create",O_CREAT|O_RDWR,0664,NULL);
	if(mdes == -1) perror("mq_open"),exit(1);
	
	reg_sig(&mdes);
 
	while(1); //main thread is doing its job; as and when the event signal(a new msg is delivered into an empty queue by other process) occured then it will halt the current process and read the msg and print it onto stdout.. and continues it halted job.
}
