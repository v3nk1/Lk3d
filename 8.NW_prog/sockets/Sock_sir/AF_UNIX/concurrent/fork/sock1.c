#include<sys/socket.h>
#include<stdio.h>
#include<linux/un.h>
#include<string.h>

#define SV_SOCK_PATH	"./mysock"

main(){

	struct sockaddr_un addr;
	int sfd;
	socklen_t len;

	sfd=socket(AF_UNIX,SOCK_STREAM,0);

	bzero(&addr,sizeof(addr));
	addr.sun_family=AF_UNIX;
	strncpy(addr.sun_path,SV_SOCK_PATH,sizeof(addr.sun_path)-1);
	len=sizeof(struct sockaddr_un);

	remove(SV_SOCK_PATH);
	bind(sfd,(struct sockaddr *)&addr,len);

	listen(sfd,5);

	while(1){

		int cfd = accept(sfd,NULL,NULL);
		printf("Yipee!! Got a client :)\n");

		switch(fork()){

		case 0:/*child*/{

			char buf[100];
			int rd=read(cfd,buf,sizeof(buf));
			printf("recvd_data: ");
			fflush(stdout);
			write(1,buf,rd);
			break;

			}

	default:
		//wait();	
		break;

		}

	}
}
