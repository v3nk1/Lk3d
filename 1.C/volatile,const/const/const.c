#include <stdio.h>

main(){

	const int ci=10;
	int i=100;
	int *pi;
	const int *pci;
	
	pi=(int *)&ci;
	*pi=20;
	printf("a=%d\n",ci);

}
