#include<stdio.h>
main(){

	int i=0,k=1,j=2;
	//i=(j++,k++);// Assigns last argument to i. ie., i=k++;
	//i=j++,k++;  // Assigns j++ to i. ie., i=j++;
	
	printf("%d %d %d\n",i,j,k);

	while(i,j,k);
		//It will take last argument(k) as condition. rest all will b neglected.
}
