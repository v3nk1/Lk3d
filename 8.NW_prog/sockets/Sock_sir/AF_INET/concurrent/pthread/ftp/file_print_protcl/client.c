#include<stdio.h>
#include<linux/in.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

#define NOTFOUND        "notfound\0"
#define FOUND           "found\0"
#define RDCOMPLETE      "EOF\0"

main(int argc,char *argv[]){

	int sfd;
	socklen_t len;
	struct sockaddr_in addr;
	char *srvip;
	
#define LOCAL 	1
#define INET	2

switch(argc){

	case LOCAL:
		srvip = "127.0.0.1";
		break;
	case INET:
		srvip = argv[1];
		break;
	default:
		printf("Usage:\n INET: %s <srverip> OR LOCAL: %s\n",argv[0],argv[0]);
		break;
	}

	char data_buf[10000]; /*shud be greater than sizeof strcmp() comparision macros */

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
	char fl_name[100];

	while(1){

		read(sfd,fl_name,sizeof(fl_name));

		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! DATA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		printf("                                                 %s\n",fl_name);
		while(1){

			bzero(data_buf,sizeof(data_buf));
			int rd = read(sfd,data_buf,sizeof(data_buf));
			sync();
//			printf("\nrd: %d\n",rd);

			if(!strcmp(data_buf,RDCOMPLETE)){
					printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
					printf("Reached EOF\n");
                               		break;
                               		}

			if(rd==0){
				printf("Server Closed\n");
				abort();
				}
			write(1,data_buf,rd);
			sync();
//			getchar();
			}

	}

}
