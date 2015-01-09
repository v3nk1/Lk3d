#include<stdio.h>

void mid_ele(int *p,int q){
	
	printf("mid_ele: %d\n",*(p+((q-1)/2)));

}

main(){
	
	int i,s;
	int a[s];
	
	printf("enter no.. array ele:");
	scanf("%d",&s);

	for(i=0;i<s;i++){
		printf("enter array ele%d: ",(i+1));
		scanf(" %d",&a[i]);
		}

	//printf("%d\n",sizeof a);
	mid_ele(a,i);

}
