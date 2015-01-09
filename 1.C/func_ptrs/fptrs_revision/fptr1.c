//HERE WE ARE DEFINING A FUCTION WHICH TAKES TWO FUCTIONS AS FORMAL ARGUMENTS & NOTHING IS RETURNED.

#include<stdio.h>

/*********************************************=> NORMAL-WAY <=********************************************
int add(int x, int y){
	return x+y;
	}

int sub(int x, int y){
	return x-y;
	}

void abc(int (*fp1)(int,int) , int (*fp2)(int,int) ){

	printf("add=%d\n",(*fp1)(11,22));
	printf("sub=%d\n",(*fp2)(11,22));

	}

***********************************************************************************************************/


/******************************************=> BY TYPEDEF <=************************************************/

typedef int (*func)(int,int); 
//so now onwards if u are encounter by func its like a data type for a function taking \
	2 intgrs as arguments and returns an integer.

int add(int x,int y){

	return x+y;
}

int sub(int x, int y){

	return x-y;

	}

void abc(func temp_add, func temp_sub){

	printf("add=%d\n",(*x)(11,22));
	printf("sub=%d\n",(*y)(11,22));

	}

/***********************************************************************************************************/


main(){

abc(add,sub);

}
