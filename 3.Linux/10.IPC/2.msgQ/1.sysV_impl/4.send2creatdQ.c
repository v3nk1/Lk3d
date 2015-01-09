//sending a msg to a specific queue(already created msgQ)..(all manipulated through comdline arg only)

#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int len;

typedef struct msgbuf {
               long mtype;       /* message type, must be > 0 */
               char mtext[1000];    /* message data */
           }msg;

	msg msgp;

void msq_details(int msqid){
	
	struct msqid_ds buf;
	msgctl(msqid,IPC_STAT,&buf);
	
	printf("created msgQid: %d  type: %ld size = %d bytes\n",msqid,msgp.mtype,len);

	printf("max no of bytes allowd in a que = %lu\n",buf.msg_qbytes);

}	


main(int argc,char *argv[]){

if(argc ==4){
	
	int msqid = atoi(argv[1]);

	len = strlen(argv[3])+1;
	msgp.mtype = atoi(argv[2]);
	strcpy(msgp.mtext,argv[3]);
	msgp.mtext[strlen(argv[3])+1]='\0';
	
//	msgp.mtype=13;
//	strcpy(msgp.mtext,"i'm legend\0");

	if(msgsnd(msqid,&msgp,len,IPC_NOWAIT|MSG_NOERROR)==-1) perror("msgsend"),exit(1);
	
	msq_details(msqid);

	}
	
else printf("Invalid argument\nUsage: sudo <executable> <msQid> <mtype> <msg(char's)>\n");

}

/***************************************************************************************************************
NOTES:
	when u run(for sending/receiving also) its neccessary that you must be a privelleged user.. "sudo ./a.out"
	
	once a msg sent to the msgQ it will be there in que until other process receives it.. after reception it will be removed..
	actually in reception it will block until until this process sends but we are using "IPC_NOWAIT" such that it behaves as non block call
************************************************************************************************************/
