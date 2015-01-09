#include"header.h" 
#include<stdio.h>
#include<string.h>    
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<stdlib.h>
#include<signal.h>

char smname[20],check[100],cmname[20],uname[20],cmd[5];
char buff[1024];
int snd,msg;//msg sent by client to server count

int main(){

    int sfd,cfd,rd;
    socklen_t len;
    struct sockaddr_in saddr,claddr;
     
    //Create socket
    sfd = socket(AF_INET,SOCK_STREAM,0);
    if (sfd == -1){
        perror("socket");
	exit(2);
    }
     
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(8888);
     
    //Bind
    if(bind(sfd,(struct sockaddr *)&saddr,sizeof(saddr)) < 0){
        perror("bind");
        return;
    }
     
    //Listen
    listen(sfd ,5);
     
    len= sizeof(struct sockaddr_in);

    printf("Enter servername: ");
    scanf(" %s",smname);

    printf("Waiting for clients..\n");

while(1){

    //accept connection from an incoming client
    cfd = accept(sfd,(struct sockaddr *)&claddr,&len);
    if(cfd < 0){
        perror("accept");
        return;
    	}

	printf("Client connecting..\n");
	//syncfs(cfd);sync();syncfs(sfd);sync();
	rd = recv(cfd,cmd,sizeof(cmd),0);
                                                               
                        if(!rd){                                                        
                                printf("Client terminated by user\n");        
                                raise(SIGKILL);                                         
                                }                                                       
                        else if(rd<0){                                                  
                                perror("recv");                                         
                                continue;                                               
                                }                                                       
                               

	if(!strcmp(cmd,SRVCHK)){
		//syncfs(cfd);sync();syncfs(sfd);sync();
	    	send(cfd,smname,sizeof(smname),0);
		recv(cfd,cmd,sizeof(cmd),0);
		if(!strcmp(cmd,ILGCLI)){ 
			printf("Denied: An unregisterd client\n");
			continue;}
		}
	sercli_t cbuff;
	int i,rcv=0;
	attr_t *battr;		//backup attr;
	switch(fork()){

		case 0:
			while(1){

			memset(&cbuff,0,sizeof(cbuff));
		//	syncfs(cfd);sync();syncfs(sfd);sync();
			rd=recv(cfd,cmd,sizeof(cmd),0);
			 if(!rd){
                                printf("A client terminatd by user\n");
                                raise(SIGKILL);
                                }
                        else if(rd<0){
                                perror("recv");
                                continue;
                                }
	
			if(!strcmp(cmd,REG)){
		//		syncfs(cfd);sync();syncfs(sfd);sync();
				recv(cfd,cmname,sizeof(cmname),0);
				printf("%s: Registerd\n",cmname);
				}
			else if(!strcmp(cmd,DREG)){
				printf("%s: Deregstrd\n",cmname);
				}
			else if(!strcmp(cmd,SND)){//srv sending..
				for(i=0;i<msg;i++){
					//syncfs(cfd);sync();syncfs(sfd);sync();
					send(cfd,battr+i,sizeof(attr_t),0);
//		write(1,buff+snd,battr[i].sndr_sz);
					snd+=send(cfd,buff+snd,battr[i].sndr_sz,0);
					//syncfs(cfd);sync();syncfs(sfd);sync();
//		write(1,buff+snd,battr[i].sub_sz);
					snd+=send(cfd,buff+snd,battr[i].sub_sz,0);
					//syncfs(cfd);sync();syncfs(sfd);sync();
//		write(1,buff+snd,battr[i].msg_sz);
					snd+=send(cfd,buff+snd,battr[i].msg_sz,0);
					}
				printf("\nAll msgs sent to client %s\n",cmname);
				free(battr);
				snd=0;
/**/				rcv=0;
				msg=0;
				}
    			else if(!strcmp(cmd,RCV)){//srv recving form client
				
				//syncfs(cfd);sync();syncfs(sfd);sync();
				recv(cfd,&cbuff,sizeof(cbuff),0);
//printf("rcv: %d\n",rcv);
//printf("sending sz: %d\n",cbuff.attr.sndr_sz+cbuff.attr.sub_sz+cbuff.attr.msg_sz);
				if(rcv==1024 || rcv+cbuff.attr.sndr_sz+cbuff.attr.sub_sz+cbuff.attr.msg_sz > 1024){
					//syncfs(cfd);sync();syncfs(sfd);sync();
					send(cfd,NOK,sizeof(NOK),0);
					continue;
					}
				else{
					//syncfs(cfd);sync();syncfs(sfd);sync();
					send(cfd,OK,sizeof(OK),0);
					}
				if(!msg)
					battr=malloc(sizeof(attr_t));
				else 
					battr=realloc(battr,sizeof(attr_t)*(msg+1));

				(battr+msg)->sndr_sz=cbuff.attr.sndr_sz;
				strcpy(buff+rcv,cbuff.sndr);
//	printf("R#%s\n",buff+rcv);
				rcv+=cbuff.attr.sndr_sz;
				(battr+msg)->sub_sz=cbuff.attr.sub_sz;
				strcpy(buff+rcv,cbuff.subjct);
//	printf("R#%s\n",buff+rcv);
				rcv+=cbuff.attr.sub_sz;
				(battr+msg)->msg_sz=cbuff.attr.msg_sz;
				strcpy(buff+rcv,cbuff.msg);
//	printf("R#%s\n",buff+rcv);
				rcv+=cbuff.attr.msg_sz;
				msg++;
				printf("%s@%s: Mail recieved\n",cbuff.sndr,cmname);
				}
		}
    	} 
}
    return 0;
}
