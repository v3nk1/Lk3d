// ARRAY OF FUNCTON PTRS;

#include<stdio.h>

int add(int x, int y){
	return x+y;
	}

int sub(int x, int y){
	return x-y;
	}

main(){

	int (*fp[2])(int ,int)={add,sub}; 
			//at the time of declaration only we can initialize, or shud initialize individully. 

	printf("%d\n",(*fp[1])(1,2));

	}

