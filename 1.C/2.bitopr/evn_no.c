#include<stdio.h>

void even(int x){

	int val;
	val = x & 1;
	val ? printf("odd\n") : printf("evn\n");
	
}

main(){

	int tmp;
	scanf("%d",&tmp);
	even(tmp);
}
