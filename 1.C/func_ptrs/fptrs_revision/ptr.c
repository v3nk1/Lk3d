#include<stdio.h>

main(){
	int *ptr=NULL;
	
	*ptr=10; // segmentation fault coz NULL is illegal to dereffer.
	
	}
