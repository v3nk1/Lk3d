#include<stdio.h>
#include<sys/socket.h>
#include<linux/un.h>
#include<string.h>

#define SV_SOCK_PATH	"./mysock"

main(){

	struct sockaddr_un addr;
	int sfd;
	socklen_t len;
	char buf[100];

	sfd=socket(AF_UNIX,SOCK_STREAM,0);
	bzero(&addr,sizeof(addr));
	addr.sun_family=AF_UNIX;
	strncpy(addr.sun_path,SV_SOCK_PATH,sizeof(addr.sun_path)-1);
	len=sizeof(struct sockaddr_un);

	bind(sfd,(struct sockaddr *)&addr,len);


	connect(sfd,(struct sockaddr *)&addr,len);
	while(1){

		printf("Enter the data to be sent to server: ");
		fflush(stdout);
		int rd=read(0,buf,sizeof(buf));
		write(sfd,buf,rd);

		}

}
