#include<stdio.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
typedef struct msg{
		char msg[100];
		int len;
		}sm;

void push_space(int tmp,int fd){
	int x=0;
	while(x++<tmp) write(fd," ",1);
	syncfs(fd);
	return;
	}

main(){
sm o[2];

int fd=open("./text_wr.c",O_RDWR|O_TRUNC|O_CREAT,0664);
int i=0,j,k;


for(i=0;i<sizeof(o)/sizeof(struct msg);i++){
	printf("enter name,len of rec%d :",i+1);
	scanf("%s%d",o[i].msg,&o[i].len);

	push_space(strlen(o[i].msg)+sizeof(o[i].len),fd);

	int p=sysconf(_SC_PAGESIZE); perror("sysconf");

	void *wptr=mmap(NULL,strlen(o[i].msg)+sizeof(o[i].len),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);perror("mmap");
	
	for(j=0;j<strlen(o[i].msg);j++) 	
		((char*)wptr)[j]=o[i].msg[j],printf("%ld\n",&((char*)wptr)[j]);
		void *temp=(char *)wptr+j; int *temp1=(int *)temp;
		*temp1=o[i].len; printf("int_pointer=%ld\n",*temp1);
	wptr=wptr+strlen(o[i].msg)+sizeof(o[i].len);
	munmap(wptr,sizeof(o));
	}

close(fd);
}
