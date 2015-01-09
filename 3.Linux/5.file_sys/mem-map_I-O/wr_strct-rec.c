#include<stdio.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
typedef struct msg{
		char msg[100];
		int len;
		}sm;

main(){
sm o[2];

int fd=open("./text_wr.c",O_RDWR|O_TRUNC|O_CREAT,0664);
//int fd=open("./text_wr.c",O_RDWR);
//char buff[sizeof(o[0].msg)];int lenn;
int i,j,k;

while(i++<sizeof(o)) write(fd," ",1);
syncfs(fd);

void *wptr=mmap(NULL,sizeof(o),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
//memset(wptr,'X',sizeof(o)); if mmap allocates successfully then only it just replaces that space with all by 'X'

for(i=0;i<sizeof(o)/sizeof(struct msg);i++){
	printf("enter name,len of rec%d :",i+1);
	scanf("%s%d",o[i].msg,&o[i].len);
	//strcpy((char *)wptr,o[i].msg); 
	//*((int *)(wptr+strlen(o[i].msg)))=o[i].len;
	//*((int *)(wptr+10))=o[i].len;
	for(j=0;j<strlen(o[i].msg);j++) //printf("loop=%d\n",j),	
		((char*)wptr)[j]=o[i].msg[j],printf("%ld\n",&((char*)wptr)[j]);
		//printf("out of loop=%d\n",j); 
		void *temp=(char *)wptr+j; int *temp1=(int *)temp;
		*temp1=o[i].len; printf("int_pointer=%ld\n",sizeof(*temp1));
	wptr=wptr+strlen(o[i].msg)+sizeof(o[i].len);
	}

munmap(wptr,sizeof(o));
close(fd);
}
