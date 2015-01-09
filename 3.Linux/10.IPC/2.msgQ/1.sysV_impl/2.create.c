//create a msgQ and see it is created or not??

#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define KEY getpid()//12345
	//if u give a constant num here every time u create a msg queue u hav to change it to other no; if u giv getpid() every tim u execute its pid will changes na.. so automatically key value also changes..
void msq_details(int msqid){
	
	struct msqid_ds buf;
	msgctl(msqid,IPC_STAT,&buf);
	
	printf("created msgQid: %d\n",msqid);

	printf("max no of bytes allowd in a que = %lu\n",buf.msg_qbytes);

}	

main(){

	int msqid = msgget(KEY,IPC_CREAT|IPC_EXCL);//here it will automatically sets errno, so we can use perror blindly.. only pthread doesnt set error no..
			//if u use IPC_CREAT only then it creates the file if it not exit, if it exits already then it will open that. if u use both IPC_CREAT|IPC_EXCL then it wil throw an error if the file is already exsisting or if not exist then it creates successfull but if u combine those 2 flags it cannt be use like a open call for an exitsting msgQ..
	
	if(msqid ==-1) perror("msgget"),exit(1);
	
	msq_details(msqid);
}

/********************************************************************************************************************************
NOTES:
``````	We can create a msgQ of sysV standard as above..
	once an messeage Q is created then it will be there(even the particular process terminated) until u delete or remove it..
	
	we can see the message queues by typing "sudo ipcs" in shell prompt..

	we can remove an ipc by a command "sudo ipcrm -q(for msgQ) <msgQid>"

*********************************************************************************************************************************/
