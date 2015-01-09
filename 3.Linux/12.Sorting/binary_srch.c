//For binary search the list shud be sorted in ascending order.. Then only do this procedure

#include<stdio.h>

int binary_srch(int a[],int key,int first,int last){

	int middle;

	while(first <= last ){
	
		middle = (first+last)/2;
	
		if(key == a[middle]) return middle;
		else if(key < a[middle])
				last = middle-1;
		else 
			first = middle+1;
		}

	return -1;

}

main(){

	int a[]={1,2,3,4,5,6,7,8,9};
	int srch;
	printf("Enter the search ele: ");
	scanf(" %d",&srch);	
	int pos;

	switch(pos = binary_srch(a,srch,0,sizeof(a)/sizeof(int))){

		case -1:
			printf("Element not found\n");
			break;
		default:
			printf("%d ele is in pos %d\n",srch,pos);
			break;
		}
}
