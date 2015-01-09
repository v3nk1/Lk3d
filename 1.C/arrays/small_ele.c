#include<stdio.h>
#include<limits.h>

main(){

	int a[5]={20,4,-10,1,3};
/*	int i,sml = INT_MAX;
	for(i=0;i<5;i++){
		if(a[i]<sml)
			sml=a[i];
	}
*/	
	int i,sml=a[0];
	for(i=1;i<5;i++)
		if(a[i]<sml)
			sml = a[i];

printf("%d\n",sml);
}
