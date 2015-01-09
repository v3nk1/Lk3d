//open argv[2] as a+ mode no need to use 1st while loop,becoz after a+ declared the file-offset already points to end of file.
//IF you open in r+ mode so you hav to make offset to endoffile.

#include<stdio.h>
#include<stdlib.h>
main(int argc,char *argv[]){
	char buf[20],i;
	FILE *src,*dst;
	src=fopen(argv[1],"r");if(!src) perror("fopen"),exit(1);
	dst=fopen(argv[2],"a+");if(!dst) perror("fopen"),exit(1);
	void *p,*q;
	/*while(1){        //this while loop is neccessary bcoz to make the file-offset to end of file if data existed in file.
		q=fgets(buf,sizeof(buf),dst);
		if(!q) break;
	}*/
	while(1){
		p=fgets(buf,sizeof(buf),src);
//getchar();
//for(i=0;i<20;i++)
//		printf("%03d--->%03d-->%c\n",i,buf[i],buf[i]);
		if(!p) break;
		fputs(buf,dst);        //then bcoz of 1st while iteration now here it is appending only.
	}
fclose(src);
fclose(dst);
}

		

