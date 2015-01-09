//prob3: memory overrun's (accessing beyond u requested for allocation);

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

main(){

	int *ptr = malloc(2*sizeof(int));

	ptr[0] = 123;
	ptr[1] = 234;

	/* we are going to use more than we requested */ 
	ptr[2] = 345;
	ptr[3] = 456;

	printf("ptr: %d, %d, %d, %d\n",ptr[0],ptr[1],ptr[2],ptr[3]);

		/*

		Here we are using more than we requested, but here case it's working bcoz of there may be available memory in Heap. But it maynot be always like this what if there was no space available in heap, so it will cause segmentation fault(or undefined behaviour)..

		*/

}
