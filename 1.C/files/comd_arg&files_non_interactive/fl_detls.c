// program to print the no of char and lines in a given file in non-interacitve-mode(ie., command line arguments)

#include<stdio.h>
#include<stdlib.h>
main(int argc,char *argv[]){
	char ch,lines[20];
	FILE *stream;
	if(argc==2){
		stream=fopen(argv[1],"r"); if(!stream) perror("fopen"), exit(1);


/*		while(1){
			ch=fgetc(stream);
			if(ch==EOF) break;
		}
		printf("num of char: %ldC  ",ftell(stream));
		rewind(stream);      */
		void *p; int cnt=0;
		while(1){//cnt++; this is giv 1 extra line becoz break condition checked down na.. so
			p=fgets(lines,sizeof(lines),stream);
			if(!p) break;
			cnt++;
		}		
		printf("num of lines: %dL  ",cnt); printf("num of char: %ldC\n",ftell(stream));
	}
	else printf("error: check operand\n");
}

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!    NOTES	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

FILE-OFFSET:  It allways incremented by no of char in a particular file. how ever you read means like a string or char ie., fgets,		fputs.
	      So ftell(stream) here always tells the file-offset no of char it read at the end of 2nd while iteration.

	 so to decide howmany line we must count how many times the while loop is executing till it reaches endoffile(EOF).
*/
