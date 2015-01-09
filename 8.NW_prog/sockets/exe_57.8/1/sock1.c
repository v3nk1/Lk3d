//Server
/*server doesnt require to know client address*/

#include<stdio.h>
#include"header.h"

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

		bzero(buff,sizeof(buff));//To remove junk values present in the local buffer
		numBytes = recvfrom(sfd,buff,sizeof(buff),0,(struct sockaddr *)&claddr,&len);
					/*we will get client_addr(claddr) and client_addrlen(len) get populated*/
		printf("\nData recvd %d bytes frm Client\n",numBytes);
		printf("data_rcv: %s",buff);//buff comes here with '\n' at last, since we press enter after input 						has given from console(stdin)

		int snt=sendto(sfd,buff,numBytes,0,(struct sockaddr *)&claddr,len);

		printf("Data has sent(%d bytes) to client: %s\n",snt,claddr.sun_path);

		}

}	
