//How to know the headers informatoin of malloc:  compile it in 32 bit also..

			// cc -m32 <name.c>	run ./a.out
			// cc <name.c>		run ./a.out

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

main(){

	int *p = malloc(0);
	//int *p = malloc(100);

	printf("%d\n",malloc_usable_size(p));
	
}
