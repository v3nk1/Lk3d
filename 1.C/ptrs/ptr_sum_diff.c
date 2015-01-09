#include<stdio.h>

void func(int x,int y,int *p,int *q){

	*p=x+y;
	*q=x-y;

}

main(){

	int sum,dif;
	int *p=&sum,*q=&dif;
	func(20,10,p,q);
	printf("%d %d\n",sum,dif);

}
