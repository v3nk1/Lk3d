#include<stdio.h>

void pb_g(unsigned long long int x,unsigned int size){

	int i;

	//for(i=size*8-1;i>=0;i--) x & 1<<i ? printf("1 "): printf("0 "); //here we are shifting "1" by i times

	for(i=size*8-1;i>=0;i--) printf("%d ",x >> i & 1); //here we are shifting "integer" by i times but not "1"

	printf("\n");

	}
