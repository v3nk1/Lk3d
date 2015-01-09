/*
 * A ptr is a ptr; which will overwrite the previous data what we wrote., irrespective of any ptr to any data type
 * just we need that ptr base address reference..
 */


#include<stdio.h>
#include<malloc.h>

struct A{
	int a;
	int b;
	};

main(){

	struct A *Aptr;

	printf("%p\n",Aptr);
//	Aptr->a=100;
//	Aptr->b=200;
	printf("%d %d\n",Aptr->a,Aptr->b);

	Aptr = malloc(sizeof(struct A));
	printf("%p\n",Aptr);

	Aptr->a=10;
	Aptr->b=20;

	printf("%d %d\n",Aptr->a,Aptr->b);

	int *ptr=Aptr;
	*ptr=200;
	*(ptr+1)=100;
	printf("%d %d\n",Aptr->a,Aptr->b);

}
