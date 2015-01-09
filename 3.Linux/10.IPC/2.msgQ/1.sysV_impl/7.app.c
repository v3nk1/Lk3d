//Implement an application which will create a child process.. child process acts like a server which will take the request from the client. Parent will act like client which will initiate the request..

	//Here parent is read some data of opened file and send it to the child using ipc(messageQ) and the child is print the data what parent has sent through messageQ..
	//like that entire file shuld be print onto runscreen..

#include<stdio.h>
#include<unistd.h>

#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<sys/ipc.h>
#include<sys/msg.h>

#define KEY getpid()

struct msgbuf {
               long mtype;       /* message type, must be > 0 */
               char mtext[100];    /* message data */
           }msg;

main(){

	int fd = open("./delete.c",O_RDONLY);
	int msqid = msgget(KEY,IPC_CREAT|IPC_EXCL);
	
		if(msqid==-1) perror("msgget"),exit(1);
	
	switch(fork()){

		case 0:/*child context*/
			//char buf[100];
//			sleep(1);
			while(1){
			
				int size = msgrcv(msqid,&msg,100,10,/*IPC_NOWAIT|*/MSG_NOERROR);
				
				if(size == -1){	
				/*deletion of msgQ(otherwise it will be there only, you can see it in "sudo ipcs"*/
					msgctl(msqid,IPC_RMID,NULL);
					break;
					}
				write(1,msg.mtext,size);
				syncfs(1);

			  }
			break;
				
		default:/*parent context*/

			msg.mtype = 10;
			char buf[100];

			while(1){
				int rd = read(fd,buf,sizeof(buf));
				if(rd==0) break;
				strcpy(msg.mtext,buf);
				if(msgsnd(msqid,&msg,rd,/*IPC_NOWAIT|*/MSG_NOERROR)) perror("msgsnd"),exit(3);
//				getchar();//to see msgQ's in "sudo ipcs"......
	
			}
				
			break;
	}

	
}
