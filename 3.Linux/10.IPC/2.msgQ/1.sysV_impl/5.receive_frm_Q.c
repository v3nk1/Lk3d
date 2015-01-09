//to receive a sent msg..

#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct msgbuf {
               long mtype;       /* message type, must be > 0 */
               char mtext[1000];    /* message data */
           }msg;

main(int argc,char *argv[]){

	msg msgp;
	if(argc == 4){

		unsigned long int size = msgrcv(atoi(argv[1]),&msgp,atoi(argv[2]),atoi(argv[3]),IPC_NOWAIT|MSG_NOERROR);
		if(size == -1) perror("msgrcv"),exit(1);

		printf("%lu bytes red(read)\n",size);
		printf("read data:\n\t%s\n",msgp.mtext);
		
		}
	else printf("invalid arguments\nUsage: sudo <executable> <msgQid> <size> <mtype>\n");
	
	
}


/*************************************************************************************************************
NOTES:
        when u run(for sending/receiving also) its neccessary that you must be a privelleged user.. "sudo ./a.out"

**************************************************************************************************************/

