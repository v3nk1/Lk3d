#include<stdio.h>

struct data{

	int a[100],sum;

	}o;

main(){

	int i;
	//struct data o;
	struct data o={1,2,3,4,5,6,7,8,9}; // here automatically compiler takes o.sum=0. 
	//o.a[100]={1,2,3};
	//o.sum=0;


	for(i=0;i<100;i++){

		o.sum=o.sum+o.a[i];

		}

	printf("%d\n",o.sum);

}
