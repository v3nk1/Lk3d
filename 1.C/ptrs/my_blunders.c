
#include<stdio.h>

main(){

	int a=50;
	printf("%lu\n",(int*)&a);
	printf("%lu\n",&a+1);               //4bytes inc
	//printf("%d\n",(int*)&a+1);        //4bytes inc
	//printf("%d\n",(int*)(&a+1));      //4bytes inc
	//printf("%d\n",(char*)&a+1);       //1byte  inc                    
	//printf("%d\n",(char*)(&a+1));     //4bytes inc

		/***********************************************************************************
		 * IN PTRS DIFFERENCE OPERATION IS VALID IF & ONLYIF THE OPERANDS ARE OF SAME TYPE *
		 ***********************************************************************************/
		//ADDINTION OF 2 PTRS ARE UNDERIVABLE.
	 
	printf("%d\n",(int)(&a+1)-(int)&a);// ==========> ans: 4

	printf("%d\n",(int *)(&a+1)-(int *)&a); //======> ans: 4/sizeof(int) = 1
	//here no need of (int *) bcoz since it basically an integer.
	//see in pointers difference operation retuns numbr of elements that can store in that type. here the diff retuns actually 4bytes, but during difference oprtn it retuns no of elements that can store enough in that 4 bytes. so here we use INT ptr so we can store only 1 ELEMENT of INTEGER type since EACH INT TYPE requires 4bytes.so it returns 1.

	printf("%d\n",(char *)(&a+1)-(char *)&a);//see in pointers difference operation it retuns nuber. Elements that   can store in that type. here the diff retuns actually 4bytes, but during difference oprtn it retuns no of elements that can store enough in that 4 bytes. so here we use CHAR ptr so we can store only 4 ELEMENTS of CHAR type since EACH CAHR TYPE requires 1byte.so it returns 4.

	printf("%d\n",(short *)(&a+1)-(short *)&a);//===> ans: 4/sizeof(short) = 2
}
