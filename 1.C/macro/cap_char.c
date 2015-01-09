//Program to check whether the given char is capital letter or not..

#include<stdio.h>

#define CAP_CHAR(ch) 	if(ch>=65&&ch<=90) printf("true\n");//printf("true\n",if(ch>=65&&ch<=90));

main(){

	char ch='D';
	CAP_CHAR(ch)

}
