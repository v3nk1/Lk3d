//Prob4: memory Under-run:(this will be illegal since we are over writing the malloc headers)

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

main(){

	int *ptr = malloc(2*sizeof(int));

	ptr[-1] = 100;
	ptr[-2] = 200;

	printf("ptr[-1]: %d\nptr[-2]: %d\n",ptr[-1],ptr[-2]);

//	free(ptr);

}

/*
	* Each time malloc invoked it will create heap memory more than size u reqested bcoz of storing "status information"(in this size we are requested and other inf is stored) and "overheads"(see vi ./glibc_malloc.c).. this information is stored in first couple of bytes and after is our data storage location..
	* And pointer(address) is returned by malloc is the address after the storate of malloc headers information. So if you decrement ptr by 1 and derefer it means *(ptr-1) = ptr[-1] so we are overwriting the headers inforation with 100.
	* This header information of malloc is very much imporent for free ing the memory by free cal, 
	In this case free call causes segmentation fault(becoz of wrong header information of malloc)..

*/
