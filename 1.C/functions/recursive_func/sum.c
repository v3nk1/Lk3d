//calculate sum by using recusive functions, dont use loops,
//It will calculate sum of 0 to 10 numbers


#include<stdio.h>

int sum(int a){
	
	if(a<10)
		return sum(a+1)+a;

}

main(){

	int val=0;
	printf("%d\n",sum(0));

}
