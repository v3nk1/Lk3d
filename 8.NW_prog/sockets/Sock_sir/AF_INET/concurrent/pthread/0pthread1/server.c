//This approach servers multi client at a time..

#include<stdio.h>
#include<stdlib.h>
#include<linux/in.h>
#include<sys/socket.h>
#include<string.h>

#include<signal.h>
#include<pthread.h>

int cl_cnt;

int cfd;/*latest client fd will be stored here, So in thread func we shud make sure it local */

struct sockaddr_in claddr;

void *thread_for_client(void *arg){

	int curr_cfd = cfd;
			/* If u dont use this, if client2 has terminated automatically client1 also terminates
			 * since bcoz cfd only holds new client fd, it will tries to connect with client2 only in client1 thread
			 * function also bcoz cfd= is global to all and its value is always latest client fd.
			 * So if dont use this statement this client1 thread tries to communicate with terminated client 1..
			 * and it fails(bcoz of rd = 0) break will execute.
			 */

	char buf[100];

	while(1){

		int rd = read(curr_cfd,buf,sizeof(buf));
		if(rd==0){
			printf("Dis_Conn: Client(%u)		(-_-)\n",claddr.sin_port);
			//For all clients claddr.sin_addr.s_addr will be same..
			//port no will be different..
			break;
			}
		//printf("Connected: Client(%u)	(o_O)\n",claddr.sin_port);
						//place it top
		printf("Data_rcv(%d B) frm client %u: ",rd,claddr.sin_port);
		fflush(stdout);
	
		write(1,buf,rd);

		}

}

main(){

	int sfd;
	socklen_t len;
	struct sockaddr_in addr;	

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

	printf("Alone!! Waiting for a client :(\n");

	while(1){//For repeated waiting for clients., but one after another only can be served
	
//	printf("%d\n",cl_cnt);
//	if(!cl_cnt)
		   cfd = accept(sfd,(struct sockaddr *)&claddr,&claddrlen);
				//Here 2nd argument is out-param,nd 3rd argment is in-param (actually sizeof 2nd arg)

			if(cfd==-1){
				perror("accept");
				exit(1);
				}
	if(!cl_cnt)
		printf("Yipeee!! Got a client :) \n\n");
		cl_cnt++;
		printf("Connectd: Client(%u)		(o_O)\n",claddr.sin_port);

	pthread_t tid;
	pthread_create(&tid,NULL,thread_for_client,NULL);
	//pthread_join(NULL); Not needed since its in while loop..
	}
	
close(sfd);

}
