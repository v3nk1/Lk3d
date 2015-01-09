//Guess the output & why??

#include<stdio.h>

main(){

	int i,x = 0x12345678;
	char *ch = (char *)&x;
	for(i=0;i<=3;i++)
		printf("%x ",*ch++);
	printf("\n");
}


/*
 * Hint:
 * How it will be stored in memory
 */
