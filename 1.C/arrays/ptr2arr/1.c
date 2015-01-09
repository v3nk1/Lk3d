//Printing an array using ptr to array concept
		// Ofcourse we can print using by passing array base address to formal arguments of called function.

#include<stdio.h>

void print_arr(int (*arr)[4]){

	int i;
	for(i=0;i<(((unsigned long)(arr+1))-(unsigned long)arr)/4;i++)
			/* In 64 bit OS 								
				If u typecasted to unsigned then, compiler will show loss of bytes bcoz	
				in 64 bit pointer size is 8bytes and intgr size is 4bytes, So there'll  
				loss of data, coz of different size.
				
				cc -m32 1.c
			 */			

			/* In 32 bit OS
				it will b normal, since ptrs size is 4bytes. intgr size is 4bytes.
			   
			 */

		printf("%d ",*(*arr+i));
	printf("\n");
}

main(){

	int arr[]={1,2,3,4};

	print_arr(&arr);

}
