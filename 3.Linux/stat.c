//man 2 stat

 #include <sys/types.h>
       #include <sys/stat.h>
       #include <time.h>
       #include <stdio.h>
       #include <stdlib.h>
main(int argc,char *argv[]){
struct stat buff;
int p=stat(argv[1],&buff);
if(p==-1) perror("stat"),exit(1);
printf("total size : %lu bytes\n",buff.st_size);
printf("user id    : %d \n",buff.st_uid);
printf("group id   : %d \n",buff.st_gid);
printf("permissions:");
	//	if(S_IRWXU & buff.st_mode)  printf("rwx------");
			 if(S_IRUSR & buff.st_mode)  printf("r");else printf("-");
			 if(S_IWUSR & buff.st_mode)  printf("w");else printf("-");
			 if(S_IXUSR & buff.st_mode)  printf("x");else printf("-");
	//	if(S_IRWXG & buff.st_mode)  printf("---rwx---");
			 if(S_IRGRP & buff.st_mode) printf("r");else printf("-");
			 if(S_IWGRP & buff.st_mode) printf("w");else printf("-");
			 if(S_IXGRP & buff.st_mode) printf("x");else printf("-");
	//	if(S_IRWXO & buff.st_mode) printf("------rwx");
			
			 if(S_IROTH  & buff.st_mode) printf("r");else printf("-");
			 if(S_IWOTH  & buff.st_mode) printf("w");else printf("-");
			 if( S_IXOTH & buff.st_mode) printf("x");else printf("-");
			
printf("\n");
}
