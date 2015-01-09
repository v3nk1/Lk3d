#include<stdio.h>
#include<linux/in.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>

main(){

	int sfd;
	socklen_t len;
	struct sockaddr_in addr;
	char *srvip = "10.0.0.4";
	char buf[100];

	sfd=socket(AF_INET,SOCK_STREAM,0);
//	perror("socket");

	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr=htonl(INADDR_ANY);

	inet_pton(AF_INET,srvip,&addr.sin_addr);
//	perror("inet");

	if(connect(sfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_in))==-1)
									perror("connect"),abort();

	while(1){
	
		printf("Enter Data: ");
		fflush(stdout);

		int rd = read(0,buf,sizeof(buf));
		int snt = write(sfd,buf,rd);
		printf("Data sent to Server(%s): %d Bytes\n\n",srvip,snt);

	}

}
