#include <stdio.h>

int _init(void)
{

	printf("My init called\n");
	return 0;

}

int _fini(void){

	printf("My fini called\n");
//	exit(0);
	return 0;

}

int add(int a,int b)
{
	return a+b;
}
