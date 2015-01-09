#include<stdio.h>

void big_ele(int *a,int sz){

	int big=a[1],i;

	for(i=0;i<(sz/4);i++){
		int temp=*(a+i);
		big = big>temp ? big : temp ;
	}

printf("%d\n",big);

}


main(){

	int a[]={1,2,300,3,2};
	big_ele(a,sizeof (a));

}


