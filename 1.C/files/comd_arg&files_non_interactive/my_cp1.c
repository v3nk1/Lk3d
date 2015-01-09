// using fgetc  & fputc..
#include<stdio.h>
#include<stdlib.h>
main(int argc,char *argv[]){
	FILE *src,*dst;
	int i;char buf;
	src=fopen(argv[1],"r"); if(!src) perror("fopen"),exit(1);
	dst=fopen(argv[2],"w"); if(!dst) perror("fopen"),exit(1);
		while(1){
			buf=fgetc(src);
			printf("%ld\n",ftell(src));
			//if(buf==EOF) break;// or we can use if(buf==-1) break;
			if(buf<0) break; //  if the reading is completd the fgetc returns EOF ie., -1 
			fputc(buf,dst);
		}
	fclose(src);
	fclose(dst);
}
