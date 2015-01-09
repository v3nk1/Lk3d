#include<stdio.h>

main(){

	int i,a;
	printf("Hex i/p: ");
	scanf("%x",&a);

	char *p=(char *)&a;
	
	for(i=0;i<3;i++)
		printf("%x",(int)p[i]);		

	printf("\n");

}
