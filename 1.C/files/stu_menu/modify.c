#include<stdlib.h>
#include<stdio.h>
extern int q;
struct stu{
        char name[25];
        char gen;
        int rolno;
        float hei;
        char grade;
};

struct stu *wbuf,*rbuf;
void modify(){
        int cnt=0;
        char name[25];
        printf("enter name:");scanf("%s",name);
        FILE *stm;
        int rolno,i;
stm=fopen("del_rec.file","r");if(!stm) perror("fopen"),exit(1);
rbuf=(struct stu *)malloc(sizeof(struct stu)*q);
fread(rbuf,sizeof(struct stu)*q,1,stm);
fclose(stm);
        wbuf=(struct stu *)malloc(sizeof(struct stu)*q);
        wbuf=rbuf;
stm=fopen("del_rec.file","w");if(!stm) perror("fopen"),exit(1);
for(i=0;i<q;i++){
        if(!strcmp(rbuf[i].name,name)) {cnt++;
                printf("enter the name gen rolno hei grade of stu%d: ",i+1);
                scanf(" %s %c %d %f %c",wbuf[i].name,&wbuf[i].gen,&wbuf[i].rolno,&wbuf[i].hei,&wbuf[i].grade);
                        }
        }
if(cnt==1) fwrite(wbuf,sizeof(struct stu)*q,1,stm);
fclose(stm);
if(cnt>1){
         wbuf=rbuf;
        stm=fopen("del_rec.file","w");if(!stm) perror("fopen"),exit(1);
        printf("\nrequired rolno also:"),scanf("%d",&rolno);
        for(i=0;i<q;i++){
		if(rbuf[i].rolno==rolno){
                printf("enter the name gen rolno hei grade of stu%d: ",i+1);
                scanf(" %s %c %d %f %c",wbuf[i].name,&wbuf[i].gen,&wbuf[i].rolno,&wbuf[i].hei,&wbuf[i].grade);
                }
        }
        fwrite(wbuf,sizeof(struct stu),q,stm);
}

free(wbuf);
//free(rbuf); //why glibc error
}

