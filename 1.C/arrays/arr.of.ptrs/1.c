#include<stdio.h>

main(){

	int a=10,b=20;
	int *arr[9];
	arr[0]=&a;
	arr[1]=&b;

	printf("%lu =-> %lu\n",arr+1,arr);
		//arr+1 increments by sizeof that type ie., sizeof(int *)=8	64-bit OS	\
									 =4 	32-bit OS
}
