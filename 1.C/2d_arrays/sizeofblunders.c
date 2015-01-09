#include<stdio.h>

main(){

	int a[2][3]={1,2,3};
	int *p=&a;		    // incompatible pointer type
	printf("%d %d\n",a,a+1);    // increments by (column size)*(type)=here 3*4=12bytes.
	printf("%d %d\n",&a,&a+1);  //increments by total array size ie., 2*3*type=2*3*4=24bytes.
	printf("%d %d\n",*p,*p+1);  //those indicates values..

}
