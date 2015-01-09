//This approach servers multi client at a time ..

#include<stdio.h>
#include<stdlib.h>
#include<linux/in.h>
#include<sys/socket.h>
#include<string.h>

#include<signal.h>

int cl_cnt;

void zobie_cleanup(int signo){

	cl_cnt--;
/* Comment if u dont want to display this msg in cosole(Stdout)
	printf("caught signal %d (%s)\n",signo,strsignal(signo));
*/
}

void reg_zobie_cleanin(void){
	/**
	 * In order to avoid ZOMBIE's we registered with auto cleanup
	 */

	struct sigaction sigac;
	bzero(&sigac,sizeof(sigac));
	sigac.sa_handler = zobie_cleanup;
	sigac.sa_flags = SA_RESTART|SA_NOCLDWAIT;
	sigaction(SIGCHLD,&sigac,NULL);
	
}


main(){

	int sfd;
	socklen_t len;
	struct sockaddr_in addr;
	char buf[100];	

	struct sockaddr_in claddr;
        socklen_t claddrlen=sizeof(claddr);//its not an out-param

	reg_zobie_cleanin();

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

		int cfd = accept(sfd,(struct sockaddr *)&claddr,&claddrlen);
				//Here 2nd argument is out-param,nd 3rd argment is in-param (actually sizeof 2nd arg)

			if(cfd==-1){
				perror("accept");
				exit(1);
				}

		if(!cl_cnt)
			printf("\nYipeee!! Got a client :) \n\n");

		cl_cnt++;
		printf("Connectd: Client(%u)		(o_O)\n",claddr.sin_port);

		switch(fork()){

			case 0:/*Child context*/
				while(1){

					int rd = read(cfd,buf,sizeof(buf));
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
				/*
				 * If u give "break" bellow then child(case:0) also executing while loop(abv switch) 
				 * along with parent(case:default).
				 * If u give return then ZOBIE PROCESS
				 */
				return;
				
			default:/*Dont make default parent to wait(), exit() or abort(), if u do it then no more listen*/ 
				break;
		}
	}
	
close(sfd);

}


/**
 * Here in parent default case generally goes back to accept and block for client connections, while the child 
 * receives data form client backgroundly..
 */
