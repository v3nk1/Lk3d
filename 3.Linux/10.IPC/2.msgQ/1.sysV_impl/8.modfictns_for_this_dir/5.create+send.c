//create a msgQ and send a msg..

#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define KEY getpid() //12345

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

if(argc ==3){

	len = strlen(argv[2])+1;
	msgp.mtype = atoi(argv[1]);
	strcpy(msgp.mtext,argv[2]);
	msgp.mtext[strlen(argv[2])+1]='\0';
	
	int msqid = msgget(KEY,IPC_CREAT|IPC_EXCL);//here it will automatically sets errno, so we can use perror blindly.. only pthread doesnt set error no..
	
	if(msqid==-1) perror("msgget"),exit(1);
	
//	msgp.mtype=13;
//	strcpy(msgp.mtext,"i'm legend\0");
	if(msgsnd(msqid,&msgp,len,IPC_NOWAIT|MSG_NOERROR)==-1) perror("msgsend"),exit(2);
	
	msq_details(msqid);
	}
	
else printf("Invalid argument\nUsage: sudo <executable> <mtype> <msg(char's)>\n");
}

/********************************************************************************************************************************
NOTES:
	when u run(for sending/receiving also) its neccessary that you must be a privelleged user.. "sudo ./a.out"

*********************************************************************************************************************************/
