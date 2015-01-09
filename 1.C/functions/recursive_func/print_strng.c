/********* MODIFY CODE TO STRING *************/

/*
 * Print an array using recursive function concept, printing normal array, printing reverse array without affecting 
 * array.. ie., printing without looping(while, for kind of things)
 */

#include<stdio.h>

int print_rev(int ele,int *a){

	if(ele)
		print_rev(--ele,a+1),
		printf("%d ",*a);
		

}

int print_norm(int ele,int *a){

	printf("%d ",*a);
	if(ele!=1)
		print(--ele,a+1);

}

main(){

	int a[5]={1,2,3,4,5};

	print_norm(5,a);
	printf("\n");

	print_rev(5,a);
	printf("\n");

}
