//To compile it use cc -w my_sizeof.c or cc -m32 my_sizeof.c Bcoz it will throw warnings becoz u are converting pointerto integer thats fine in 32 bit since both pointer and interger size is of 4 bytes, on 64 bit machines its like loosing some bytes in type cast so warning will thrown.

#include<stdio.h>

int my_sizeof(int a){

	return (int)(&a+1)-(int)&a;

}

main(){

	int a=50;
	
	printf("%d\n",my_sizeof(a));
	//printf("%p\n",(char*)&a);
	//printf("%p\n",(char*)(&a+1));
	//printf("%d\n",(&a++)-&a);

}
