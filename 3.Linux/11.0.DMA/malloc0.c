#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

main(){

	int *ptr; //since i want to store 2 interges in the memory allocated by malloc()

//	getchar(); //to see the heap allocation before and after malloc() in "cat /proc/<pid_of_curr_proccess>/maps"
	
	if((ptr = malloc(2*sizeof(int)))==NULL) printf("malloc: Unable to allocate mem in heap\n"),exit(1); //no need to typecast malloc returned void ptr to (int *)
	printf("*ptr(initial_state) = %d(garbage)\n",*ptr);
	
	printf("\nSTATS:\n");
	malloc_stats();

	*ptr = 10;
	printf("*ptr = %d\n",*ptr);

//	getchar(); //again see "cat /proc/<pid_of_curr_proccess>/maps"

	free(ptr);

	printf("*ptr after free = %d\n",*ptr);
	
//	getchar();  //again see to check that heap allocated is removed or not?  So it wont removed free() just flush it to 0 & mark that location as reusable..
}
