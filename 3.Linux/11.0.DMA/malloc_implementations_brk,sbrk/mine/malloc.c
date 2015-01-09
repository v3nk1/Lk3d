#include <stdio.h>
#include <stdlib.h>

main(int argc,char **argv){

	int *p=NULL, a,b;
	if(argc!=2){
		printf("Usage: %s <size>\n",argv[0]);
		return;
		}
//	mallopt(M_MAP_THRESHOLD,)
	printf("BP before malloc: %d\n",a=sbrk(0));
	p=malloc(atoi(argv[1]));
	if(!p)
		printf("Malloc failed\n"),
		exit(1);

	malloc_stats();	

	printf("BP after malloc: %d\n",b=sbrk(0));

	printf("diff: %d\n",b-a);

}
