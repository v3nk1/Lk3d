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
void add(){
        FILE *stm;
	int n_add=0,i;
        printf("\nhow many records:");
        scanf("%d",&n_add);q+=n_add;
        wbuf=(struct stu *)malloc(n_add*sizeof(struct stu));
if(n_add>=1){
        for(i=0;i<n_add;i++) {
        printf("enter the name gen rolno hei grade of stu%d: ",i+1);
        scanf(" %s %c %d %f %c",wbuf[i].name,&wbuf[i].gen,&wbuf[i].rolno,&wbuf[i].hei,&wbuf[i].grade);
        }
stm=fopen("del_rec.file","a");if(!stm) perror("fopen"),exit(1);
fwrite(wbuf,sizeof(struct stu)*n_add,1,stm);
fclose(stm);
free(wbuf);
}
else printf("ERROR IN INPUT\n");
}

