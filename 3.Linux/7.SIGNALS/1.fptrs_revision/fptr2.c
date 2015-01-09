//NOW WE ARE CREATING A FUNCTION THAT TAKES 2 FUCTIONS AS ARGUMENTS AND RETURN ANOTHER FUNCTION.

#include<stdio.h>
/*********************************************************=> NORMAL-WAY <=**********************************************************************/

int add(int x, int y){
	return x+y;
	}

int sub(int x, int y){
	return x-y;
	}

void def(int x, char y){
	printf("def_address= %p\n",def);		

	}

void (*abc(int (*fp1)(int ,int ) , int (*fp2)(int , int )) )  (int, char) {

	return def;

}

main(){
	void (*fp)(int , char);
	def(1,'c');
	fp= abc(add,sub);
	printf("returned= %p\n",fp);

}

