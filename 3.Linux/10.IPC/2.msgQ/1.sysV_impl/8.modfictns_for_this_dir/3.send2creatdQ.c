//sending a msg to a specific queue(already created msgQ)..(all manipulated through comdline arg only)

#include"./headers.h"

void msq_details(int msqid){
	
	struct msqid_ds buf;
	msgctl(msqid,IPC_STAT,&buf);
	
	printf("created msgQid: %d  type: %ld size = %d bytes\n",msqid,msgp.mtype,len);

	printf("max no of bytes allowd in a que = %lu\n",buf.msg_qbytes);

}	


main(int argc,char *argv[]){

if(argc ==3){
	
	int msqid = msgget(KEY,IPC_CREAT); //we are opening a already created msgQ for this u shudnt pass IPC_EXCL;
	
	len = strlen(argv[2])+1;
	msgp.mtype = atoi(argv[1]);
	strcpy(msgp.mtext,argv[2]);
	msgp.mtext[strlen(argv[2])+1]='\0';
	
	if(msgsnd(msqid,&msgp,len,IPC_NOWAIT|MSG_NOERROR)==-1) perror("msgsend"),exit(1);
	
	msq_details(msqid);

	}
	
else printf("Invalid argument\nUsage: sudo <executable> <mtype> <msg(char's)>\n");

}
