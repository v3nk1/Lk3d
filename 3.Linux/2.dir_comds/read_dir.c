#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<dirent.h>

main(int argc,char *argv[]){

	if(argc<=1) printf("command not found\n");
	else{
	DIR *p=opendir(argv[1]);
	if(p==NULL) perror("opendir"),exit(1);
	struct dirent *ptr;
	while(1){
		ptr=readdir(p);
		if(ptr==NULL) break;

		printf("%s ",ptr->d_name);
		}
	printf("\n");
	}
}
