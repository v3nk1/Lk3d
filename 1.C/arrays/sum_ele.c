#include<stdio.h>

int sum_ele(int *p,int q){

	int i,temp=0;

	for(i=(q/4)-1;i>=0;i--){
		temp=temp+*(p+i);
		//p++;
		//printf("%u\n",p);
		}

	return temp;

}

main(){

	int sum,a[]={1,2,3,5};
	sum=sum_ele(a,sizeof (a));
	printf("sum: %d\n",sum);

}
