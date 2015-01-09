//notify an event by thread new;

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#include <mqueue.h>
#include <signal.h> //for strsignal()
#include <string.h>


void rec_mesg(void *ptr_mdes){

        mqd_t mdes = *(mqd_t *)ptr_mdes;
        char buf[100];

        struct mq_attr attr;
        mq_getattr(mdes,&attr);

        int size = attr.mq_msgsize +1;

        int rcv = mq_receive(mdes,buf,size,NULL); //i'm not interested inn the readed msg priority val(so i passed NULL)
        if(rcv == -1) perror("mq_receive"),exit(3);

        /*the problem with printf here is printf invoked last ie., after system call write, since 1st system call are invoked and then API's*/
//      printf("Recieved msg: ");
        write(1,"Received msg: ",14);
        write(1,buf,rcv); //writing the received msg onto "STDOUT"

        printf("\n");

}

void threadFunc(union sigval val){

	printf("thread is created for receive the sent msg: %lu\n",pthread_self());
	printf("passed ptr: %p\n",val.sival_ptr);
	rec_mesg(val.sival_ptr);
	
}

void notifysetup(mqd_t *mdesp){

	struct sigevent eve;
	eve.sigev_notify = SIGEV_THREAD;
//	eve.sigev_value.sival_int = 1234; bellow we are using one of the union member(void *sival_ptr); so dont use it
	eve.sigev_notify_function = threadFunc;
	eve.sigev_notify_attributes = NULL;
		
	eve.sigev_value.sival_ptr = mdesp;

	mq_notify(*mdesp, &eve);  //here registering event notification for msg arrival by "mq_notify" api

}
	
main(){

	mqd_t mdes;
	mdes = mq_open("/create",O_RDONLY);
	notifysetup(&mdes);
	pause();
	//while(1);

}
