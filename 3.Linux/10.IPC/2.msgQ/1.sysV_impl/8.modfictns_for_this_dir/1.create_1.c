//to open a created msgQ for a key given in the "./headers.h"
#include"./headers.h"

void msq_details(int msqid){
	
	struct msqid_ds buf;
	msgctl(msqid,IPC_STAT,&buf);
	
	printf("created msgQid: %d\n",msqid);

	printf("max no of bytes allowd in a que = %lu\n",buf.msg_qbytes);

}	

main(){

	int msqid = msgget(KEY,IPC_CREAT);//here it u shudnt give IPC_EXCL flag, if u give this function is not anymore used for opening a created msgQ
	
	if(msqid ==-1) perror("msgget"),exit(1);
	
	msq_details(msqid);
}
