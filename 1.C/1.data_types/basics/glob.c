#include<stdio.h>

extern int a;

/*void function(void);*/

main(){
	
	printf("glob: %d\n",a);
	a=20;
	function();
}

/*void*/int function(void){ 
	/*
	 * Actually it needs declaration but if u specify return type as int it will work fine.
	 * But if u place void then error raises that implicit declaration of function
	 *
	 */
	
		printf("faltu\n");

	}

int a=10;
