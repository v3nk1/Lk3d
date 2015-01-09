//Server(which handles one client at a time)
//Server recieves some data from client and prints it onto the console

#include<stdio.h>
#include"header.h"
#define BACKLOG 5

main(){

	struct sockaddr_un svaddr;
	int sfd, cfd;
	char buf[BUF_SIZE];
	int rd;

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
		if(sfd==-1){
			perror("socket");
			exit(1);
			}

	remove(SOCK_PATH);
	memset(&svaddr, 0, sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path,SOCK_PATH, sizeof(svaddr.sun_path)-1);

	bind(sfd,(struct sockaddr *)&svaddr,sizeof(struct sockaddr_un));

	listen(sfd, BACKLOG);
	
	for (;;){//To accept many clients, this odd loop is for that so.
		
		printf("Alone!! Waiting for a client :(\n");
		cfd = accept(sfd,NULL,NULL);//It will block here until a client sock connected
		printf("Got a Client!! Cheers :)\n");
		if(cfd==-1)
			perror("accept"),exit(1);

		/* Transfer data from connected socket to stdout until EOF */
		while(1){
			rd=read(cfd,buf,BUF_SIZE);//if client sock has closed then read will return 0, so rd=0;
			if(rd==0){ 
				printf("Client has closed\n");
				break;//to respond to other connection if serving client has terminated, Or put read					API in while loop condition instead of 1.
			//recvfrom();
				}
			printf("data red: %d bytes from client\n",rd);
			printf("data: ");
			fflush(stdout);//to print above printf
			write(1,buf,rd);
			}
		}

	close(sfd);//Be concious while writing close.. if u write in above while loop blunder..

}
