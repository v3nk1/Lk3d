#include<stdio.h>
#include<linux/in.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>

#define NOTFOUND        "notfound\0"
#define FOUND           "found\0"
#define RDCOMPLETE      "EOF\0"

main(){

	int sfd;
	socklen_t len;
	struct sockaddr_in addr;
	char *srvip = "127.0.0.1";
	char buf[100]; /*shud be greater than sizeof strcmp() comparision macros */

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
	
		printf("Enter Filename: ");
		fflush(stdout);
		int rd = read(0,buf,sizeof(buf));
		int snt = write(sfd,buf,rd);
			if(snt==-1){
				printf("Serverip Invalid\n");
				break;
				}
		printf("Data sent to Server(%s): %d Bytes\n\n",srvip,snt);

		read(sfd,buf,sizeof(buf));/* if file found it will read 1st 100 bytes here only */

		if(!strcmp(buf,NOTFOUND)){
			printf("File not found\n");
			continue;
			}

		if(!strcmp(buf,FOUND)){
				printf("File found\n");
				printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! DATA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				}

		while(1){

			bzero(buf,sizeof(buf));
			rd = read(sfd,buf,sizeof(buf));
//			printf("\nrd: %d\n",rd);

			if(!strcmp(buf,RDCOMPLETE)){
					printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
					printf("Reached EOF\n");
                               		break;
                               		}

			if(rd==0){
				printf("Server Closed\n");
				abort();
				}
			write(1,buf,rd);
//			getchar();
			}

	}

}
