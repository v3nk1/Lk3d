#include<stdio.h>

pb(unsigned int i){

int temp;
for(temp=8*sizeof(i)-1;temp>=0;temp--){
	
	if((temp+1)%8==0) printf("  ");  //for getting space for every 8 bits
	(i&(1<<temp)) ? printf("1 "):printf("0 ");

	}

printf("\n");

}                             
