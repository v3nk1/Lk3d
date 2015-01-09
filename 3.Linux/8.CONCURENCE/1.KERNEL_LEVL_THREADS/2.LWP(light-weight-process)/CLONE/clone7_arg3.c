// so we can pass a value to the child thread by clone using 4th argument of clone..

#define _GNU_SOURCE
#include<stdio.h>
#include<sched.h>

#define STACK_SIZE 12000

int thread_func(void *agr){ // here agr is the the address of our passed variable, so to use it we have to typecast first and dereference next.

	printf("thread execution startd\n");
	printf("passed value by clone() is: %d\n",*((int *)agr)); // without typecast error will occur..

}

main(){

	
	void *stack_alloc = malloc(STACK_SIZE);
	
	int pas_val = 1234;  // create a variable of any type and pass its address as 4th argument..

	clone(thread_func, stack_alloc+STACK_SIZE, CLONE_VM|CLONE_FILES, &pas_val);
	
	sleep(10);
	
	printf("default thread(main) ended\n");

}

