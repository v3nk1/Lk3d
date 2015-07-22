//This approach servers single client at a time and the remaining clients has thrown into wait queue..

#include<stdio.h>
#include<stdlib.h>
#include<linux/in.h>
#include<sys/socket.h>
#include<string.h>

main(){

	int sfd;
	socklen_t len;
	struct sockaddr_in addr;
	char buf[100];	

	struct sockaddr_in claddr;
        socklen_t claddrlen=sizeof(claddr);//its not an out-param


	sfd=socket(AF_INET,SOCK_STREAM,0);
//	perror("socket");

	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	bind(sfd,(struct sockaddr *)&addr,sizeof(struct sockaddr));
//	perror("bind");	

	listen(sfd,5);
//	perror("listen");

	while(1){//For repeated waiting for clients., but one after another only can be served

		printf("\nAlone!! Waiting for a client :(\n");
		int cfd = accept(sfd,(struct sockaddr *)&claddr,&claddrlen);
				//Here 2nd argument is out-param,nd 3rd argment is in-param (actually sizeof 2nd arg)

			if(cfd==-1){
				perror("accept");
				exit(1);
				}
		printf("Yipeee!! Got a client :) \n\n");
		printf("Connectd: Client(%s:%u)		(o_O)\n",inet_ntoa(claddr.sin_addr),claddr.sin_port);

		while(1){

			int rd = read(cfd,buf,sizeof(buf));
			if(rd==0){
				printf("Dis_Conn: Client(%u)		(-_-)\n",claddr.sin_port);
						//For all clients claddr.sin_addr.s_addr will be same..
						//port no will be different..
				break;
				}
			//printf("Connected: Client(%u)	(o_O)\n",claddr.sin_port);
						//place it top
			printf("Data_rcv(%d B): ",rd);
			fflush(stdout);

			write(1,buf,rd);
		}
	}
	
close(sfd);

}
