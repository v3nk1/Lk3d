//Client
/*But client has to know servers address(path) inorder to connect with server */
#include<stdio.h>
#include"header.h"

main(){

        int sfd,rd;
	struct sockaddr_un svaddr,claddr;
	char buff[100],rd_buf[100];
	socklen_t len;

	remove(SOCK_CL_PATH);

	claddr.sun_family = AF_UNIX;
	strncpy(claddr.sun_path,SOCK_CL_PATH,sizeof(claddr.sun_path));

    	sfd=socket(AF_UNIX,SOCK_DGRAM,0);
	
	bind(sfd,(struct sockaddr *)&claddr,sizeof(struct sockaddr_un)-1);

	/*Constructing server sock address*/
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path,SOCK_SV_PATH,sizeof(svaddr.sun_path));

	len=sizeof(struct sockaddr_un);

	while(1){

		//write(1,"Enter data to be sent server: ",30); Or
		printf("\nEnter data to be sent server: ");	//printf alone doent invoke first
		fflush(stdout);

		bzero(rd_buf,sizeof(rd_buf));
		bzero(buff,sizeof(buff));

		rd = read(0,rd_buf,sizeof(rd_buf));
		printf("Data read from console %d bytes\n",rd);/*It will read including '\n' */
	
		int snt = sendto(sfd,rd_buf,rd,0,(struct sockaddr *)&svaddr,len);/*sent including '\n'*/
		printf("Data sent to Server %d bytes\n",snt);

		int rcv = recvfrom(sfd,buff,sizeof(buff),0,(struct sockaddr *)&svaddr,&len);
		printf("\nData rcv from Server %d bytes\n",rcv);
		printf("rcv: %s",buff);/*Data recived including '\n' */

		}

}	
