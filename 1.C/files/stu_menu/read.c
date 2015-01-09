#include<stdlib.h>
#include<stdio.h>
struct stu{
        char name[25];
        char gen;
        int rolno;
        float hei;
        char grade;
};

struct stu *rbuf;
extern int q;    
void read(){
   if(q==0) printf("NO DATA IN FILE\n");
   else{
        int i;
        FILE *stm;
        stm=fopen("del_rec.file","r");if(!stm) perror("fopen"),exit(1);
        rbuf=(struct stu *)malloc(sizeof(struct stu)*q);
        fread(rbuf,sizeof(struct stu)*q,1,stm);
        fclose(stm);
        printf("present data in file\n");
for(i=0;i<q;i++) {
        printf(" %-10s %c %2d %.1f %c\n",rbuf[i].name,rbuf[i].gen,rbuf[i].rolno,rbuf[i].hei,rbuf[i].grade);
        }
free(rbuf);
    }
//free(rbuf); its an error becoz, see suppose q=0 then if block only executes,then w/o declaring a dynamic memory we are freeing that causes error.
}

