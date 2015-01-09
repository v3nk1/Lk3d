// USING FPUTC FUNCTION


#include<stdio.h>
#include<stdlib.h>
main(){
//FILE *fp;
char *pc="i'm doin files";
FILE *fp;
fp=fopen("crt_fl_wr.file","w");
if(!fp) {perror("fopen");exit(1);}
int i=0;
while(pc[i++]) fputc(pc[i-1],fp);// or u can use        while(pc[i]) fputc(p[i],fp),i++;
//while(pc[i++]) fputc(pc[--i],fp); its an infinite loop
fputc("\n",fp)//fprintf(fp,"\n"); //HERE WE ARE USING IT BECOZ WE REQIRE \n
fclose(fp);
}
