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
void prnt_num_of_rec(){
        FILE *stm;
        stm=fopen("del_rec.file","r");if(!stm) perror("fopen"),exit(1);
        rbuf=(struct stu *)malloc(sizeof(struct stu));
        int p;
        q=0;
while(1){
        p=fread(rbuf,sizeof(struct stu),1,stm);
        if(!p) break;q+=p;
        }
printf("no of records in current file:%d\n",q);
free(rbuf);
}

