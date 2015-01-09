//malloc prob1: MEMORY LEAKS(we lost the reference address of mem-location)

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

void mem_alloc(int *ret){

	ret = malloc(2*sizeof(int));  //this allocated mem in heap is alive till the entire program terminates, even if the mem_alloc() fuction distroyes this will be alive.. Since once the memory allocated in heap is distoroyed(freed) only if prog terminates(freed by using free() call).
	if(ret == NULL){ 
			exit(2);
		}

}

main(){

	int *ret;
	mem_alloc(ret);      
		/* to avoid this 
			1. Return the (int *) ie., "ret"(base addrs) of allocated memory from mem_alloc() function. so before distroying the mem_alloc() function if u give return statement the value u are passing is moved to accumulator register(cpu register eax) {these concepts u've seen in assembly programming},and then the stack allocated for local variables of mem_alloc() function.
			SO total mem_alloc() function distroyed.. and we catch the returned reference of allocated mem is to another ptr in main();

					OR 

			2. Call-by-reference pass '&ret' to mem_alloc func.. so that the mem_alloc() function updates the reference ptr to ret.. so no leakage.. we can use it obviously.. But in mem_alloc() function to catch passed '&ret' we must use "int **tmp" as argument..

		*/
	*ret = 1000;
	printf("val = %d\n",*ret);

}
