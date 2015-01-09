#include<stdio.h>
#include<stdlib.h>

struct stu{

	int a;
	int b;

	struct stu *ptr;
	
//	struct stu stu1; its an incomplete type, since if u uncomment it at the time of this statement the stu structure is not completed..

}

main(){

	struct stu a;
	a.ptr = &a;

	printf("%p\n",a.ptr);

}
