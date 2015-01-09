#include<stdio.h>

int main(){

	int a=10,b=20;
	printf("%s: Invoked\n",__func__);
	printf("%d\n",add(a,b));
//	printf("%d\n",sub(a,b));
	return 0;
}
