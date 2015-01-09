//Client
//Client sents some data to server

#include "header.h"

main(){

	struct sockaddr_un addr;
	int sfd;
	ssize_t rd;
	char buf[BUF_SIZE];

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);

	memset(&addr, 0, sizeof(struct sockaddr_un));
	
	/*Construct server address inorder to connect server*/
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path,SOCK_PATH,sizeof(addr.sun_path)-1);

	connect(sfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_un));

	while(1){

		write(1,"Enter data to be sent to server: ",33);
		rd = read(0,buf,BUF_SIZE);
		write(sfd, buf, rd);

		}

	close(sfd);

}
