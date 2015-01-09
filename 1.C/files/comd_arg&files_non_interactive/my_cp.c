//You hav to compile and run ./a.out followed by source and destination file names must be given,source file name must be preexisted when u run the program. it works like cp test.c testing.c

#include<stdio.h>
#include<stdlib.h>
main(int argc,char *argv[]){
	FILE *src,*dst;
	char buf[25]; //we need a buffer to store the readed by gets.
	src=fopen(argv[1],"r");
	if(!src) perror("fopen"),exit(1);
	dst=fopen(argv[2],"w");
	if(!dst) perror("fopen"),exit(1);
	//int *p; compiler throwsoff a warning incompatible assignment of pointer
	void *p;
		while(1){
			p=fgets(buf,sizeof(buf),src);
	//		printf("%ld\n",ftell(src)); //it tells that wts the pos the file offset is to perforn RD/WR operations.

			if(!p) break; // here only you must put break, otherwise ie.,if u put break after fputs then another already completed line again readed becoz of loop running after there is returnig a null i.e., previous line again printed,bcoz of file offset.

			//printf("%s",buf); //to check what they read in char array buf.
			//getchar(); // to print buf by pressing enter.

			fputs(buf,dst);
		}
	fclose(src);
	fclose(dst);
}
