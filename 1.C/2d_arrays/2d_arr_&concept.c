#include<stdio.h>
main(){
int a[3][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}};

a    =   returns ptr to array of 4(col size) integers ie., indicates addresses of 1,2,3,4
&a   =   returns ptr to array of 12 integers, total elements address
*a   =   returns ptr to integer ie., 1 address only
**a  =   returns integer ie., returns 1;

a+1      increments by col size ie., 4*4=16bytes ie now (a+1) points to 2nd row ie., 5,6,7,8
&a+1     increments by total array size ie., 3*4*sizeof(data type)=48 bytes
*a+1	 here *a indicates ptr to integer,ie.,here 1 address only. and it increments by 4 bytes so now it pointing to 2nd row 0th ele. ie.,here 	 it points to address of 5.   
*(*a+1)	 here it prints 5. 
*(a+1)	   a+1 points to total 2nd row addresses. now *(a+1) returns an integer 5.
**a+1	   **a returns integer ie.,here 1 and add 1 to it.
**(&a+1)   here in this location garbage value is presented.
***(&a)	   &a    holds 3 rows addresses but prints 0 th element address.
	   *(&a) holds 2 rows addresses but prints 0 th element address.
	   **(&a) holds 1 row adress    but prints 0 th element address
	   ***(&a) returns integer at base address. it also prints 0th element ie., prints 1.
***(a+1)   **(a+1)=5 ; ***(a+1) invalid.
***(&(a+1)) error,INVALID.
***&a+1    =**a+1
