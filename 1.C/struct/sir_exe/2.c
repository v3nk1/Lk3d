#include<stdio.h>

struct data{

	int a,b,*p,*q;

}o;

main(){

	o.p=&o.a;o.q=&o.b;
	printf("%d --- %d\n",o.p,o.q);

}
