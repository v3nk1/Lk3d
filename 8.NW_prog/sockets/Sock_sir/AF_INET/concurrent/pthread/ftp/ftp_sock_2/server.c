/*Server*/
//METHOD:2(using normal read/write calls)
	/*Sending data using just strings(char arrays) buffer only*/

#include<pthread.h>
#include"header.h"

int cl_cnt;

int cfd;/*latest client fd will be stored here, So in thread func we shud make sure it local */

struct sockaddr_in claddr;

void *thread_for_client(void *arg){

	int curr_cfd = cfd;
	struct sockaddr_in curr_claddr;
	flinfo_t flinf;
	int rd,fl_fd,wr;
	int sntB=0;/*to hold total sent bytes to client*/

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

	int blink=0,rot=0;
		/* blink= To maitain a fixed string */
		/* rot= To print sequetial, illusion like rotations*/


        unsigned int _B; /*dash B means kb or mb*/
        float flsz=0;/*Human understandable format*/
        char suff[3];

        flinf.szB=lseek(fl_fd,0,SEEK_END);/*it wil also moves offset to EOF*/
        lseek(fl_fd,0,SEEK_SET);
	
	/*Sending file info to client*/
	write(curr_cfd,&flinf,sizeof(flinf));

        if(flinf.szB/1000000 > 0){/*MB*/
                sprintf(suff,"%s","MB");
                flsz=(float)flinf.szB/1000000;
                _B=MB;
                }
        else if(flinf.szB/1000 > 0){/*KB*/
                sprintf(suff,"%s","KB");
                flsz=(float)flinf.szB/1000;
                _B=KB;
                }
        else {
                sprintf(suff,"%s","B ");
                _B=B;
                }

	
	while(1){

		bzero(&data_buf,sizeof(data_buf));
		rd = read(fl_fd,data_buf,sizeof(data_buf));
		sync();
		if(rd==0){

			/*To replace "Sending   " to "Sent"*/
			printf("\b\b\b\b\b\b\b       \b\b\b\b\b\b\b");
                        switch(_B){
                                case MB:
                                        printf("t %.1f MB(%d B)",(float)sntB/1000000,sntB);
                                        break;
                                case KB:
                                        printf("t %.1f KB(%d B)",(float)sntB/1000,sntB);
                                        break;
                                case B:
                                        printf("t %d B",sntB);
                                        break;
                                }

			fflush(stdout);
			printf("\nReached EOF\n");
			
			sync();

			close(fl_fd);
			goto loop;

			}

		sync();
		wr=write(curr_cfd,data_buf,rd);
		sync();/* Or use syncfs(); */
		sntB+=rd;/*To count how many bytes sent to client*/

		if(wr<=0){
			printf("\nDis_Conn: Client(%s:%u)		(-_-)\n",inet_ntoa(curr_claddr.sin_addr),curr_claddr.sin_port);
			break;
			}	
		

		if(!blink)//To print it only once
			printf("\nData: Sending   ");
		blink++;

		if(rot==4)// To make arr subscript value with in 4; range: 0,1,2,3
			rot=0;
		
                switch(_B){/*bcoz of <1000 bytes file switch came here,see the case:B middle argument*/

                        case MB:
                                if(sntB/1000000 > 0)
                                        printf("[%5.1f MB/%5.1f %s]  ",(float)sntB/1000000,flsz,suff);
                                else if(sntB/1000 > 0)
                                        printf("[%5.1f KB/%5.1f %s]  ",(float)sntB/1000,flsz,suff);
                                else
                                        printf("[%5d B /%5.1f %s]  ",sntB,flsz,suff);
                                fflush(stdout);
                                break;
                        case KB:
                                if(sntB/1000 > 0)
                                        printf("[%5.1f KB/%5.1f %s]  ",(float)sntB/1000,flsz,suff);
                                else
                                        printf("[%5d B /%5.1f %s]  ",sntB,flsz,suff);
                                fflush(stdout);
                                break;
                        case B:
                                printf("[%5d B /%5d %s]  ",sntB,flinf.szB,suff);
                                fflush(stdout);
                                break;
                        }

		printf("(%c)",arr[rot++]);
		fflush(stdout);
		printf("\b\b\b   \b\b\b");

		printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                     \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		sync();/* Or use syncfs(); */
		
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
		printf("Connectd: Client(%s:%u)		(o_O)\n",inet_ntoa(claddr.sin_addr),claddr.sin_port);

	pthread_t tid;
	pthread_create(&tid,NULL,thread_for_client,NULL);
	//pthread_join(NULL); Not needed since its in while loop..
	}
	
close(sfd);

}
