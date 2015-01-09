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
void del(){
        int cnt=0;
        char name[25];
        printf("enter name:");scanf("%s",name);
        FILE *stm;
        int rolno,i;
        stm=fopen("del_rec.file","r");if(!stm) perror("fopen"),exit(1);
        rbuf=(struct stu *)malloc(sizeof(struct stu)*q);
fread(rbuf,sizeof(struct stu)*q,1,stm);
fclose(stm);
        stm=fopen("del_rec.file","w");if(!stm) perror("fopen"),exit(2);
        wbuf=(struct stu *)malloc(sizeof(struct stu)*q-1);
for(i=0;i<q;i++){
        if(strcmp(rbuf[i].name,name)) wbuf[i-cnt]=rbuf[i]; //here i-cnt is very importen to make the deleted skip and make a sequence.
        else cnt++;
        }
if(cnt==1) fwrite(wbuf,sizeof(struct stu),q-1,stm);
fclose(stm);
//free(wbuf);

if(cnt>1){

        stm=fopen("del_rec.file","w");if(!stm) perror("fopen"),exit(3);
        printf("\nrequired rolno also:"),scanf("%d",&rolno);
        cnt=0;
        wbuf=(struct stu *)malloc(sizeof(struct stu)*q-1);
        for(i=0;i<q;i++){
                if(rbuf[i].rolno!=rolno) wbuf[i-cnt]=rbuf[i];
                else cnt++;
 		}
        fwrite(wbuf,sizeof(struct stu),q-1,stm);
	//free(wbuf);
        fclose(stm);
}
free(wbuf);// again memory map, core dumped. bceoz where u intialise dynamic memory there only u can free na..? think guys.
free(rbuf);
}

