//This approach servers multi client at a time..

#include<stdio.h>
#include<stdlib.h>
#include<linux/in.h>
#include<sys/socket.h>
#include<string.h>

#include<signal.h>
#include<pthread.h>
#include<fcntl.h>


#define NOTFOUND	"notfound\0"
#define FOUND		"found\0"
#define RDCOMPLETE	"EOF\0"
	/**
	 * We have to send including '\0' since we are using strcmp() on client side to know the status
	 */


#define SIZE_RDCOMP	4 /* Including '\0' */
#define SIZE_NTFND	9 /* Including '\0' */
#define SIZE_FND	6 /* Including '\0' */

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
	char fl_name[100];
	int rd,fl_fd,wr;
	int sntB=0;/*to hold total sent bytes to client*/

	bzero(buf,sizeof(buf));
	bzero(fl_name,sizeof(fl_name));

loop:
	sntB=0;/*Making fresh, for new file byte count*/
	rd = read(curr_cfd,fl_name,sizeof(fl_name));

	if(rd==0){
		printf("Dis_Conn: Client(%u)		(-_-)\n",claddr.sin_port);
		pthread_exit(NULL);
		}

	fl_name[rd-1]='\0';//Overwrite '\n' with '\0'. Since file name shudnt contain '\n' at last.

	printf("Data_rcv(%d B) frm client %u: ",rd,claddr.sin_port);
	fflush(stdout);
	write(1,fl_name,rd);

	fl_fd = open(fl_name,O_RDONLY);

		if(fl_fd==-1){
				printf("\n%s: File not found, Send again\n",fl_name);
				write(curr_cfd,NOTFOUND,SIZE_NTFND);
				goto loop;

				}
		write(curr_cfd,FOUND,SIZE_FND);
		//syncfs(curr_cfd);  Not needed
/*very very IMP*/syncfs(fl_fd);/* Otherwise it'll mis 1st 100 bytes */
				/*
				 * To optimize the System calls compiler will just call 
				 * write only after buffer fulled
				 * to change that behaviour we will use 'syncfs(fd)' or 'sync()'
				 */
	
	int blink=0,rot=0;
		/* blink= To maitain a fixed string */
		/* rot= To print sequetial, illusion like rotations*/
	char arr[]={'-','\\','|','/'};

	while(1){

		rd = read(fl_fd,buf,sizeof(buf));

		if(rd==0){

			/*To replace "Sending   " to "Sent"*/
			printf("\b\b\b\b\b\b\b       \b\b\b\b\b\b\bt (%d B)",sntB);
			fflush(stdout);

			printf("\nReached EOF\nSend a file Name ..?!?\n");

			write(curr_cfd,RDCOMPLETE,SIZE_RDCOMP);
			close(fl_fd);

			goto loop;

			}

		wr=write(curr_cfd,buf,rd);
		sntB+=wr;/*To count how many bytes sent to client*/

		if(!blink)//To print it only once
			printf("\nData: Sending   ");
		blink++;

		if(rot==4)// To make arr subscript value with in 4; range: 0,1,2,3	
			rot=0;
		printf("(%c)",arr[rot++]);
		fflush(stdout);
		printf("\b\b\b   \b\b\b");


//		write(1,buf,rd);
//		printf("\nwr: %d\n",wr);
		syncfs(fl_fd);/* Or use sync(); */
		
		if(wr==0){
			printf("\nDis_Conn: Client(%u)		(-_-)\n",claddr.sin_port);
			break;
			}	
		
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
