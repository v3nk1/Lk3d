//prob2: Dangling ptr (ptr points to invalid mem reference);

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

main(){

	int *p = malloc(2*sizeof(int));

	p[0] = 10; 
	p[1] = 20;
	
	printf("p: %d, %d\n",p[0],p[1]);

	free(p);
//	p = NULL;

	/*Now p is a dangling ptr*/  
	printf("p: %d, %d\n",p[0],p[1]);

	//to avoid dangling ptr's immediatly assign p to NULL after free(); such that if u want to access that it will cause sigmentation fault.. since *(NULL) causes error..

}
