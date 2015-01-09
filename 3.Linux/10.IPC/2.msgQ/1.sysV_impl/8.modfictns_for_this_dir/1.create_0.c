//to create a msgQ to a specified key in the "./headers.h"


#include"./headers.h"

void msq_details(int msqid){
	
	struct msqid_ds buf;
	msgctl(msqid,IPC_STAT,&buf);
	
	printf("created msgQid: %d\n",msqid);

	printf("max no of bytes allowd in a que = %lu\n",buf.msg_qbytes);

}	

main(){

	int msqid = msgget(KEY,IPC_CREAT|IPC_EXCL);//here it will automatically sets errno, so we can use perror blindly.. only pthread doesnt set error no..
	
	if(msqid ==-1) perror("msgget"),exit(1);
	
	msq_details(msqid);
}

