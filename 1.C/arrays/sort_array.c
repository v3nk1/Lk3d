#include<stdio.h>

void print(int *arr,int n){

	int i;
	for(i=0;i<n;i++)
		printf("%d ",arr[i]);
		
	printf("\n");

}

void sort(int *arr,int n){

	int cnt=0;
	int i,j,tmp;
	for(i=0;i<n-1;i++)
		for(j=i+1;j<n;j++){
			cnt++;
			if(arr[i]>arr[j]){
				tmp=arr[i];
				arr[i]=arr[j];
				arr[j]=tmp;
				}
			}
	printf("cnt: %d\n",cnt);

}

main(){

	int a[10]={4,3,2,1,-1,-2,-3,-8,99,6};
	print(a,10);
	sort(a,10);
	print(a,10);	
}
