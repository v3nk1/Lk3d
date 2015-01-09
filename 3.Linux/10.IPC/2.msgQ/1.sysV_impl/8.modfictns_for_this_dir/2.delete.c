//to delete a created msgQ.. for we must pass the "msqid" of created msgQ.. so i used command line arg implementation to do this..

#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

main(int argc,char *argv[]){

	if(argc==2){
	
		msgctl(atoi(argv[1]),IPC_RMID,NULL);//here u must use (atoi or atoil or strtoul) kindof converstion to convert string to integer..
		perror("msgctl");

		}	
	else printf("argument missing:\nUsage: <executable> <msQid>\n");

}



/*

NOTES:
        we can remove an ipc by a command "sudo ipcrm -q(for msgQ) <msgQid>"

*/
