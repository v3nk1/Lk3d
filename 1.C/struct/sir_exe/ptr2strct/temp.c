//this prog is created bcoz of to know  what will be the sizeof "array of struct ptrs *o[20]".. it will be vary from 32 bit and 64bit compilers..


#include<stdio.h>

struct abc{

	int a;

}*o[20];

main(){

	printf("%lu\n",sizeof(o));


}	

