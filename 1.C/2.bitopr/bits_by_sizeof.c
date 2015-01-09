#include<stdio.h>

int p_b(unsigned long int a){

	int i;
	for(i=(sizeof(a)*8)-1;i>=0;i--){
	a&(1<<i) ? printf("1 "):printf("0 ");
	
	}

printf("\n");

}

main(){

	unsigned long int a;
	printf("enter a value:");
	scanf("%d",&a);
	p_b(a);

}
