#include<stdio.h>

struct data{

	int a,b;

}o1={2,3},o2; // here we cant directly assingn o1 to o2, here we only assign constant values.

main(){

	o2=o1;
	printf("%d %d\n",o1.a,o1.b);
	printf("%d %d\n",o2.a,o2.b);

}
