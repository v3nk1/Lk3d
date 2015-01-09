/*Client*/
	/**
	 * Here in this approach we'll know that sender completes sending, or sending file reached end of file(eof)
	 * by a variable(eof) in pack_t structure.., if that is came to client as set then the client decides 
	 * Which one is last packet..
	 */

//	./cli for local communication or ./cli <inetaddr_server> for different host comm.,

//	The received file will store in ./recvfiles

#include "header.h"

char *find_filename(char *flname){

	char *ret;
	char tmp_flname[100];

	sprintf(tmp_flname,"%s",flname);
	mkdir("./recvfiles",0775);
	
	if(!(ret = strrchr(flname,'/'))){
			/*To get a recvd file into ./recvfiles/ */
			sprintf(flname,"recvfiles/%s",tmp_flname);
			//printf("****%s\n",flname);
			return flname;
			}
	sprintf(flname,"recvfiles/%s",ret+1);
	return flname;

}

main(int argc,char *argv[]){

	int sfd;
	socklen_t len;
	struct sockaddr_in addr;
	char *srvip;
	pack_t rcv;

#define LOCAL   1
#define INET    2

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

//	char data_buf[200000]; /*shud be greater than sizeof strcmp() comparision macros */

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
	flinfo_t flinf;
	char *nw_name;

	int blink=0,rot=0;
                /* blink= To maitain a fixed string */
                /* rot= To print sequetial, illusion like rotations*/

	while(1){

		int crtfd;
		int rcvB=0;
	        unsigned int _B; /*dash B means kb or mb*/
	        float flsz=0;/*Human understandable format*/
	        char suff[3];

		bzero(&flinf,sizeof(flinf));
		blink=0;
		
		/*Getting file information from server*/
		read(sfd,&flinf,sizeof(flinf));

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

loop:		
		nw_name = find_filename(flinf.name);
		
		crtfd = open(nw_name,O_RDWR|O_CREAT|O_EXCL,0666);
		if(crtfd==-1){
				perror("open");
				printf("Enter new file name: ");
				scanf(" %[^\n]",flinf.name);
				goto loop;
				}

		while(1){

			int rd;
			bzero(&rcv,sizeof(rcv));
			sync();
			read(sfd,&rcv,sizeof(rcv));
//			printf("packet recieved\n");
			sync();
			rd = rcv.data_sz;
			if(rcv.eof==1){

				printf("\b\b\b\b\b\b      \b\b\b\b\b\b");
	                        switch(_B){

        	                        case MB:
                	                        printf(" Accomplished %.1f MB(%d B)/%.1f MB(%d B) into ./%s\n",(float)rcvB/1000000,rcvB,flsz,flinf.szB,nw_name);
                       	                	break;
                                	case KB:
                	                        printf(" Accomplished %.1f KB(%d B) into ./%s\n",(float)rcvB/1000,rcvB,nw_name);
                                        	break;
                                	case B:
                	                        printf(" Accomplished %d B into ./%s\n",rcvB,nw_name);
                                        	break;
                                	}
					sync();
		                        fflush(stdout);
					close(crtfd);
                               		break;//its a loop break
					break;//while break
                                	}

			if(!blink)//To print it only once
		                        printf("\nData: Syncing   ");
                	blink++;

       		        if(rot==4)// To make arr subscript value with in 4; range: 0,1,2,3
	                        rot=0;

	                switch(_B){/*bcoz of <1000 bytes file switch came here,see the case:B middle argument*/

        	                case MB:/*%5.1f means: example 299.324 rounded to 299.3*/
                	                if(rcvB/1000000 > 0)
                        	                printf("[%5.1f MB/%5.1f %s]  ",(float)rcvB/1000000,flsz,suff);
                                	else if(rcvB/1000 > 0)
                                        	printf("[%5.1f KB/%5.1f %s]  ",(float)rcvB/1000,flsz,suff);
                             	   	else
                                        	printf("[%5d B /%5.1f %s]  ",rcvB,flsz,suff);
                                	fflush(stdout);
                                	break;
                        	case KB:
                                	if(rcvB/1000 > 0)
                                        	printf("[%5.1f KB/%5.1f %s]  ",(float)rcvB/1000,flsz,suff);
                                	else
                                        	printf("[%5d B /%5.1f %s]  ",rcvB,flsz,suff);
                                	fflush(stdout);
                                	break;
                        	case B:
                                	printf("[%5d B /%5d %s]  ",rcvB,flinf.szB,suff);
                                	fflush(stdout);
                                	break;

	                        }

	                printf("(%c)",arr[rot++]);
	                fflush(stdout);
	                printf("\b\b\b   \b\b\b");
			printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                     \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");

			sync();
			rcvB+=write(crtfd,rcv.data_buf,rcv.data_sz);
//			perror("write");
			sync();

			}

	}

}
