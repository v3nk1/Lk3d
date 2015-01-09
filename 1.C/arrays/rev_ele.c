/*
 * Function which will reverse the given array and store in itself.
 */

#include<stdio.h>

void rev_pos(int *p,int s){

	int i;
	int tmp;
	for(i=0;i<s/2;i++){
		//here in condition i<s/2 is neccessary., 					\
		if u run i<s same output will appear., since reswapping swapped values

		printf("Before: %d | %d\n",p[i],p[s-1-i]);
		tmp=p[i];
		p[i]=p[s-1-i];//Here s-1 shud b given since 's' is elements, the subscript value is 's-1'
		p[s-1-i]=tmp;
		printf("After : %d | %d\n",p[i],p[s-1-i]);
		}

}

main(){

	int s,i;
	printf("enter no.. ele of array: ");
	scanf("%d",&s);
	int a[s];

	for(i=0;i<s;i++){
		printf("enter ele%d: ",i+1);
		scanf(" %d",&a[i]);
		}

	printf("\nGIVEN: ");
	for(i=0;i<s;i++)
		 printf("%d ",a[i]);

	printf("\n\n");
	rev_pos(a,s);

	printf("\nRESULT: ");
	for(i=0;i<s;i++) 
		printf("%d ",*(a+i));
	printf("\n");

}
