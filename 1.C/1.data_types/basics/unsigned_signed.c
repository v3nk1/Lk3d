//Never compare signed and unsigned in conditions, those will give unpridictable results.

#include<stdio.h>

main(){
	int a=-5;
	unsigned int b=1;
	
	if(a>b)	
		printf("a is big\n");

	else 
		printf("b is big\n");

}
