//BY USING FPUTS


#include<stdio.h>
#include<stdlib.h>
main(){
char *p="i'm now using FPUTS function";
FILE *stream;
stream=fopen("wr_file","w");
if(!stream) perror(fopen),exit(1);
fputs(p,stream);
fclose(stream);
}
