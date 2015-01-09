//to receive all sent msgs at a time..

#include"./headers.h"

main(int argc,char *argv[]){

		int msqid = msgget(KEY,IPC_CREAT); //opening a specif mesgQ by its unique key given by me in header file
	
		struct msqid_ds buf;
		msgctl(msqid,IPC_STAT, &buf);
		printf("Num of msgs in the specified Q: %u\n",buf.msg_qnum);
	
		int i=0;
		while(i++<buf.msg_qnum){
		
			unsigned long int size = msgrcv(msqid,&msgp,1000,0,IPC_NOWAIT|MSG_NOERROR);
			if(size == -1) perror("msgrcv"),exit(1);
			printf("%lu bytes red(read)\n",size);
			printf("read data:\n\t%s\n",msgp.mtext);
		}

}
