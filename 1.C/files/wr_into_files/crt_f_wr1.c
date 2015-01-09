//BY USING FPRINTF


#include<stdio.h>
#include<stdlib.h>
main(){
FILE *stream;
char i=0,*p="i'm doin all file concepts";
stream=fopen("wr_f_by_lines.file","w");
if(!stream) perror(fopen),exit(1);
fprintf(stream,"%s",p);
//while(p[i++]) fputc(p[i-1],stream);

fclose(stream);
}
