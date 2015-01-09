#include<stdio.h>

int sum_rec(int i){

	int sum;
	if(i<10)
		sum=sum_rec(i+1);
	 return i+sum;
	
}

main(){

	printf("%d\n",sum_rec(1));

}
