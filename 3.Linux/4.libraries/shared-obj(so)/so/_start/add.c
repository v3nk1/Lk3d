#include<stdio.h>

int _start(){

	printf("%s: Invoked\n",__func__);
	main();
	_fini();
	exit(0);
}

int main(){

	int a=10,b=20;
	printf("%d\n",add(a,b));
	return 0;
}
