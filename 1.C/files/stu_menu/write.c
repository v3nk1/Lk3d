#include<stdlib.h>
#include<stdio.h>
struct stu{
        char name[25];
        char gen;
        int rolno;
        float hei;
        char grade;
};

struct stu *wbuf,*rbuf;
extern int q;
void write_fresh(){
	int i,n=0; 
        printf("enter no of students:");
        scanf("%d",&n); //printf("========================%d",n);
if(n==0) printf("CHECK THE ENTERED NO..\n");
else{	
	wbuf=(struct stu *)malloc(sizeof(struct stu)*n);
	for(i=0;i<n;i++){
        	printf("enter the name gen rolno hei grade of stu%d:",i+1);
        	scanf(" %s %c %d %f %c",wbuf[i].name,&wbuf[i].gen,&wbuf[i].rolno,&wbuf[i].hei,&wbuf[i].grade);
        	}
	FILE *stream;
	stream=fopen("del_rec.file","w"); if(!stream) perror("fopen"), exit(1);
	fwrite(wbuf,sizeof(struct stu)*n,1,stream);q=n;
	fclose(stream);
	}
free(wbuf);
}
