/*HERE SEGMENTATION FAULT WILL OCCUR, SINCE IT'S A RECURSING ACTION(ie., FUCTION CALLS IT SELF), IN THIS CASE IT NEVER END PROCESS.

	SEGMENTATION FAULT CAUSES ARE ONLY 2:
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		1. WHEN U R TRYING TO ACCESS ILLEGAL MEMORY, ie., u are not declared but trying to access
		2. STACK OVERFLOW, ie., when there is no stack for allocating memory for particular process variables.	

		so here every time it allocates 1lack bytes to temp for every recursive function independently in userspace since  		its a recursive, so after some point there will be no more space in stack. so cpu throws a segmentation fault.

*/

#include<stdio.h>
int cnt;

void stack_overflow(int i){
	char temp[100000];
	printf("cnt=%d\n",++cnt);//according to c standards evry printf has terminated with escape sequence ie.,like \n \t \b \a
	//printf("end of main\n"); 
	
	stack_overflow(i);

}


main(){
	
	stack_overflow(1);
	printf("end of main\n");//it's a non-executable statement. since above function is recursive.

}
