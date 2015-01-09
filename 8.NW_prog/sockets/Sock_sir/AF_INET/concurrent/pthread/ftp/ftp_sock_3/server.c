/*Server*/

//METHOD:3( using sendfile() API)

#include<pthread.h>
#include"header.h"
#include<sys/sendfile.h>

int cl_cnt;

int cfd;/*latest client fd will be stored here, So in thread func we shud make sure it local */

struct sockaddr_in claddr;

void *thread_for_client(void *arg){

	int curr_cfd = cfd;
	struct sockaddr_in curr_claddr;
	flinfo_t flinf;
	int rd,fl_fd,sntB=0;/*to hold total sent bytes to client*/

loop:
	bzero(&flinf,sizeof(flinf));

	sntB=0; /*Making it fresh*/
	printf("Enter file name to send: ");
	fflush(stdout);

	rd = read(0,flinf.name,sizeof(flinf.name));
	flinf.name[rd-1]='\0';//Overwrite '\n' with '\0'. Since file name shudnt contain '\n' at last to open().

	fl_fd = open(flinf.name,O_RDONLY);
		if(fl_fd==-1){
				printf("%s: File not found, Enter again\n",flinf.name);
				goto loop;
				}
	
	flinf.szB=lseek(fl_fd,0,SEEK_END);
	lseek(fl_fd,0,SEEK_SET);
	
	write(curr_cfd,&flinf,sizeof(flinf));

	printf("Data: Sending");
	fflush(stdout);

	sntB=sendfile(curr_cfd,fl_fd,NULL,flinf.szB);

	printf("\b\b\b\b    \b\b\b\bt (%d B)\n",sntB);

	goto loop;

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
