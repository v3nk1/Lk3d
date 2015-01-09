//Normally compile it.

#include<stdio.h>
#include<string.h>
#include"msg.h"
#include"list.h"
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>

int reg,snd,sfd,choice;
struct sockaddr_in saddr;
char smname[20],cmname[20];

void registerr(void){

	if(reg){
		printf("Server:client Machine already registered\n");
		return;
		}
	reg++;
	send(sfd,REG,sizeof(REG),0);
	send(sfd,cmname,sizeof(cmname),0);
	recv(sfd,cmd,sizeof(cmd),0);
	if(!strcmp(NOK,cmd)){
		printf("\nRegistration failed\n");
		fflush(stdout);
		return;
		}
	
    	printf("Registered with server(%s)\n",smname);
	return;
     
}

void deregister(void){
	if(!reg){
		printf("Server: First register\n");
		return;
		}
	reg--;
	send(sfd,DREG,sizeof(DREG),0);
	send(sfd,cmname,sizeof(cmname),0);
	recv(sfd,cmd,sizeof(cmd),0);
	if(!strcmp(NOK,cmd)){
		printf("First register\n");
		fflush(stdout);
		return;
		}
	printf("Deregister with server(%s)\n",smname);
	return;
}

sercli_t sbuff;

void compose(void){
	
	if(!reg){
		printf("Server: First register\n");
		return;
		}

	send(sfd,RCV,sizeof(RCV),0);
	memset(&sbuff,0,sizeof(sbuff));
	printf("\nSender[usr@client]: ");
	fflush(stdout);
	scanf(" %s",sbuff.sndr);
	sbuff.attr.sndr_sz=strlen(sbuff.sndr)>18 ? 19 :strlen(sbuff.sndr)+1;
	sbuff.sndr[19]='\0';

	printf("Destination[usr@client]: ");
	fflush(stdout);
	scanf(" %s",sbuff.dest);
	strcpy(sbuff.dest,strchr(sbuff.dest,'@')+1);
	sbuff.attr.dest_sz=strlen(sbuff.dest)>18 ? 19 :strlen(sbuff.dest)+1;
	sbuff.dest[19]='\0';

	printf("Enter Subject[0-80]:\n\t");
	fflush(stdout);
	scanf(" %[^\n]",sbuff.subjct);
	sbuff.attr.sub_sz= strlen(sbuff.subjct)>79 ? 80 : strlen(sbuff.subjct)+1;
	sbuff.subjct[80]='\0';

        printf("Enter message[0-512]: \n\t");
	fflush(stdout);
        scanf(" %[^\n]",sbuff.msg);
	
	sbuff.attr.msg_sz= strlen(sbuff.msg)>511 ? 512 : strlen(sbuff.msg)+1;
	sbuff.msg[512]='\0';			
        if(send(sfd,&sbuff,sizeof(sbuff),0)< 0){
            perror("Send");
            return ;
        }
	recv(sfd,cmd,sizeof(cmd),0);
	if(!strcmp(EBUFF,cmd)){
		printf("\nGiven buffer had Filled\n");
		fflush(stdout);
		return;
		}
	else if(!strcmp(ILGCLI,cmd)){
		printf("\nServer: Send failed(destination client not registered)\n");
		return;
		}
	snd++;
	printf("Mail sent to server@%s\n",smname);
}



void receive(void){

	memset(&sbuff,0,sizeof(sbuff));
	if(!reg){
		printf("server: First register\n");
		return;
		}
	if(send(sfd,SND,sizeof(SND),0)<0) {perror("send");return;}
	send(sfd,cmname,sizeof(cmname),0);
	int k;
	recv(sfd,INT,sizeof(INT),0);
	for(k=0;k<atoi(INT);k++){
		recv(sfd,&sbuff,sizeof(sbuff),0);		
        	printf("\nSENDER : %s\n\n",sbuff.sndr);
		printf("SUBJECT: %s\n\n",sbuff.subjct);
		printf("MSGBODY:\n\t %s\n",sbuff.msg);
		}
        snd=0;
	return;
}

void menu(void){
	while(1)
	{
		printf("\n1.Register the system\n");
		printf("2.De register the system\n");
		printf("3.Compose/send a message\n");
         	printf("4.Receive All Messages\n");
                printf("5.Exit\n\n");
		printf("Enter your choice: ");
		scanf(" %d",&choice);

		switch(choice){
			case 1:
				registerr();
   				break;
			case 2: 
				deregister();
				break;
			case 3: 
				compose();
				break;
			case 4:
				receive();
				break;
			case 5: 
				exit(1);
				break;
			default: 
				printf("No such Option\n");
				break;
			}
	}
}

int main(int argc , char *argv[]){

	if(argc != 2)
		printf("Error: %s <server-name>\n",argv[0]),
		exit(4);
	printf("Enter client machine name: ");
	scanf(" %s",cmname);

	sfd = socket(AF_INET,SOCK_STREAM,0);
    	if (sfd == -1){
       	 printf("Could not create socket\n");
	 return;
    	}

    	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    	saddr.sin_family = AF_INET;
    	saddr.sin_port = htons(8888);
 
    	if(connect(sfd,(struct sockaddr *)&saddr,sizeof(saddr)) < 0){
        perror("connect");
        return; 
    	}
     
	send(sfd,SRVCHK,sizeof(SRVCHK),0);
	recv(sfd,smname,sizeof(smname),0);
	if(strcmp(smname,argv[1])){
		send(sfd,ILGCLI,sizeof(ILGCLI),0);
		printf("Authentication failed\n");
		close(sfd);return;
		}
	else{	send(sfd,OK,sizeof(OK),0);}
	menu();
}	
