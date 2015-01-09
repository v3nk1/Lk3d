//Server
/*server doesnt require to know client address*/

#include<stdio.h>
#include"header.h"

void conv_upCase(char *buff,int sz){

	int i;
	for(i=0;i<sz;i++)
		if(buff[i]>=97 && buff[i]<=122)
					buff[i]-=32;

}

main(){

        int sfd;
	struct sockaddr_un svaddr,claddr;
	char buff[100];
	int numBytes;
	socklen_t len;

	remove(SOCK_SV_PATH);
	
	bzero(&svaddr,sizeof(svaddr));
	bzero(&claddr,sizeof(claddr));

	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path,SOCK_SV_PATH,sizeof(svaddr.sun_path)-1);

    	sfd=socket(AF_UNIX,SOCK_DGRAM,0);
	
	bind(sfd,(struct sockaddr *)&svaddr,sizeof(struct sockaddr_un)-1);

	len=sizeof(struct sockaddr_un);

	while(1){
		
		bzero(buff,sizeof(buff));

		printf("Alone!! waiting for Client :(\n");
		numBytes = recvfrom(sfd,buff,sizeof(buff),0,(struct sockaddr *)&claddr,&len);
					/*we will get client_addr(claddr) and client_addrlen(len) get populated*/
		printf("Yipee!! Got a Client :)\n");

		printf("\nData rcv from Client %d bytes\n",numBytes);
		printf("data_rcv: %s\n",buff);

		conv_upCase(buff,numBytes);
		numBytes = sendto(sfd,buff,numBytes,0,(struct sockaddr *)&claddr,len);
		printf("Data sent to Client %s: (%d bytes)\n",claddr.sun_path,numBytes);

		}

}	
