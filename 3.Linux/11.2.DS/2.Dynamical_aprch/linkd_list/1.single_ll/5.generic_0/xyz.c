#include<stdio.h>

typedef struct temp{
		int a;
		char ch;
		}tmp;

main(){

	char str1[]="venkatesh",str2[10];

	str2 = str1;  //its not permittable, to copy like that use strcpy function..


	tmp o1={1234,'A'};
	tmp o2 = o1;//its permittable

	}
