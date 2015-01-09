#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include"header.h"

int reg,snd,sfd,choice;
struct sockaddr_in saddr;
char smname[20],cmname[20],tname[20],tsub[81],tmsg[513];

void registerr(void){

	if(reg){
		printf("Server:client Machine already registered\n");
		return;
		}
	reg++;
//	sync();syncfs(sfd);sync();
	send(sfd,REG,sizeof(REG),0);
//	sync();syncfs(sfd);sync();
	send(sfd,cmname,sizeof(cmname),0);
    	printf("Registered with server(%s)\n",smname);
	return;
     
}

void deregister(void){
	if(!reg){
		printf("Server: First register\n");
		return;
		}
	reg--;
//	sync();syncfs(sfd);sync();
	send(sfd,DREG,sizeof(DREG),0);
	printf("Deregister with server(%s)\n",smname);
	return;
}

sercli_t sbuff;

void compose(void){
	
	if(!reg){
		printf("Server: First register\n");
		return;
		}

//	sync();syncfs(sfd);sync();
	send(sfd,RCV,sizeof(RCV),0);//instructs the server for to recieve what client sends
	memset(&sbuff,0,sizeof(sbuff));
	printf("\nEnter user name: ");
	fflush(stdout);
	scanf(" %s",tname);
	sbuff.attr.sndr_sz=strlen(tname)>18 ? 19 :strlen(tname)+1;//including NUL
	tname[19]='\0';
	strcpy(sbuff.sndr,tname);

	printf("Enter Subject[0-80]:\n\t");
	fflush(stdout);
	scanf(" %[^\n]",tsub);
	sbuff.attr.sub_sz= strlen(tsub)>79 ? 80 : strlen(tsub)+1;//including NUL
	tsub[80]='\0';
	strcpy(sbuff.subjct,tsub);

        printf("Enter message[0-512]: \n\t");
	fflush(stdout);
        scanf(" %[^\n]",tmsg);
	
	sbuff.attr.msg_sz= strlen(tmsg)>511 ? 512 : strlen(tmsg)+1;//including NUL
	tmsg[512]='\0';			//if given msg > 512 then no null terminated. its done explicitly.
	strcpy(sbuff.msg,tmsg);

        //Send some data
//	sync();syncfs(sfd);sync();
        if(send(sfd,&sbuff,sizeof(sbuff),0)< 0){
            perror("Send");
            return ;
        }
//	sync();syncfs(sfd);sync();
	recv(sfd,cmd,sizeof(cmd),0);
	if(!strcmp(NOK,cmd)){
		printf("\nGiven buffer had Filled\n");
		fflush(stdout);
		return;
		}
	snd++;
	printf("Mail sent to server@%s\n",smname);
//printf("%d %d %d\n",sbuff.attr.sndr_sz,sbuff.attr.sub_sz,sbuff.attr.msg_sz);
         
}



void receive(void){

	memset(tname,0,sizeof(tname));
	memset(tsub,0,sizeof(tsub));
	memset(tmsg,0,sizeof(tmsg));
	if(!reg){
		printf("server: First register\n");
		return;
		}
	if(!snd){
		printf("server: No sent messages\n");
		return;
		}
//	sync();syncfs(sfd);sync();
	if(send(sfd,SND,sizeof(SND),0)<0) {perror("send");return;}//instruct d server for sending	
	int k;
	attr_t attr;
	for(k=0;k<snd;k++){
//		sync();syncfs(sfd);sync();
		recv(sfd,&attr,sizeof(attr),0);		//getting back, sizes from server.

	        recv(sfd,tname,attr.sndr_sz/*sizeof(tname)*/,0);	//Here sizeof(tname) will read more char than 										required. but those char will discared.
        	printf("\nSENDER : %s@%s\n\n",tname,cmname);
//		sync();syncfs(sfd);sync();
	        recv(sfd,tsub,attr.sub_sz,0);
		printf("SUBJECT: %s\n\n",tsub);
//		sync();syncfs(sfd);sync();
	        recv(sfd,tmsg,attr.msg_sz,0);
		printf("MSGBODY:\n\t %s\n",tmsg);
//printf("%d %d %d\n",attr.sndr_sz,attr.sub_sz,attr.msg_sz);
		}
        snd=0;
	return;
}

void menu(void){
	//Menu creation
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
     
//	sync();syncfs(sfd);sync();
	send(sfd,SRVCHK,sizeof(SRVCHK),0);
//	sync();syncfs(sfd);sync();
	recv(sfd,smname,sizeof(smname),0);
	if(strcmp(smname,argv[1])){
		send(sfd,ILGCLI,sizeof(ILGCLI),0);
		printf("Authentication failed\n");
		close(sfd);return;
		}
	else{	send(sfd,OK,sizeof(OK),0);}
//	strcpy(smname,argv[1]);
	menu();

}	
