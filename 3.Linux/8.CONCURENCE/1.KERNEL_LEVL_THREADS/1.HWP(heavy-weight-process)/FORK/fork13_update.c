//To know that, if u update a value in child, is it also effecting the parent or not??

	//here it will use a concept called "copy-on-write".


#include<stdio.h>
#include<unistd.h>

main(){

	int i=10,j=20;
	printf("before fork: i=%d,j=%d\n",i,j);

	switch(fork()){

		case 0:
			printf("after fork in child: i = %d, j = %d\n",++i,j);
			break;
	
		default:
			printf("after fork in parent: i = %d, j = %d\n",i,++j);
			break;
		}

	printf("Last: i=%d, j=%d\n",i,j);
}


/*********************************************************************************************************************************
NOTES:
``````	See from the point at which fork() invoked, then another process called child is created. it wil hav its own resources		 PCB and ADDRESS_SPACE. After that modify the child those modifications are updated only in its own resouces.
	If u change any data of parent(above fork only dont expect this in default: case) then it will take a copy of that to child.

*********************************************************************************************************************************/
