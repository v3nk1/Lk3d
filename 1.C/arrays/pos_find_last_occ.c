#include<stdio.h>

void pos_find(int *p,int s,int ele){
	
	int i=s-1;
	for(;i>=0;i--){
		if(ele==*(p+i)){
			 printf("pos is %d of that array:\n",i);
			 return; 
			}          /////////////////////
		}
	printf("invalid ele\n");

}

main(){

	int s,i,ele;
	int a[s];
	
	printf("enter no.. ele of array:");
	scanf("%d",&s);
	
	for(i=0;i<s;i++){
		printf("enter ele%d:\n",i+1);
		scanf(" %d",&a[i]);
		}

	printf("enter an ele u wnt 2 find pos:");
	scanf("%d",&ele);
	pos_find(a,s,ele);

}
