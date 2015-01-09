//prog to print alter records.

#include<stdio.h>
#include<stdlib.h>

struct stu{
        char name[25];
        char gen;
        int rolno;
        float hei;
        char grade;
};

struct stu *buff;

main(){
	int n,i;	
	printf("enter no..of stu:");
	scanf("%d",&n);
	FILE *stream;
	stream=fopen("srch.file","r"); if(!stream) perror("fopen"),exit(1);
	buff=(struct stu *)malloc(n*sizeof(struct stu));
	fread(buff,sizeof(struct stu)*n,1,stream);  //correct reads all objects. ie.,at a time read 1 block of data of size 2nd argument.
	//fread(buff,sizeof(struct stu),n,stream);    //correct reads all objects. ie., at a time read n blocks of data of size 2nd argument.
	//fread(buff,sizeof(struct stu),1,stream);      //wrong, reads only one structure obj,ie., here naresh, i.e first one and store in buff[0] object only, buff[1][2]][3] are empty.
//printf("%s\n",buff[0].name);
	fclose(stream);
if(n%2) 
for(i=0;i<=n/2;i++) 
printf("\ni=%d %s\t %c\t %d\t %.1f\t %c\n",i,buff[2*i].name,buff[2*i].gen,buff[2*i].rolno,buff[2*i].hei,buff[2*i].grade);
else 
for(i=0;i<n/2;i++) 
printf("\ni=%d %s\t %c\t %d\t %.1f\t %c\n",i,buff[2*i].name,buff[2*i].gen,buff[2*i].rolno,buff[2*i].hei,buff[2*i].grade);

}
