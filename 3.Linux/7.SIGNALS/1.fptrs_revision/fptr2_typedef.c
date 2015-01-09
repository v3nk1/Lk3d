//NOW WE ARE CREATING A FUNCTION THAT TAKES 2 FUCTIONS AS ARGUMENTS AND RETURN ANOTHER FUNCTION  "USING TYPE DEF".

#include<stdio.h>
/*********************************************************=> TYPE DEF <=**********************************************************************/

typedef int (*func)(int , int);

int add(int x, int y){
	return x+y;
	}

int sub(int x, int y){
	return x-y;
	}

void def(int x, char y){
	printf("def_address= %p\n",def);		

	}

typedef void (*ret_func)( int , char ); // we need to declare it. we cannt use previous one becoz func has the signature that it takes 2 int and return int. Now here ret_func takes int & char as arguments and nothing return.

ret_func abc(func temp_add, func temp_sub) {

	return def; //returns def function address 

}

main(){
	void (*fp)(int , char);
	def(1,'c');
	fp= abc(add,sub);
	printf("returned= %p\n",fp);

}

