#include<stdio.h>
#include<stdlib.h>


main(){
	int i=0;

	while(1){ 

		printf("%d\n",i);
		if(i==10) abort();  // i want to abort the program when loop encounters with i==10; 
		i++; 

		}

	}
