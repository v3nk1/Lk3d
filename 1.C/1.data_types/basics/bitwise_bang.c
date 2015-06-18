#include <stdio.h>
#include <stdlib.h>

void pb(unsigned long long u_64,int bytes){

	int i;
	for(i=bytes*8-1;i>=0;i--){
		if(i!=bytes*8-1 && !((i+1)%4))
			printf(" ");
		printf("%lld",u_64>>i & 1U);
		}
	printf("\n");

}

#define PB(val) {\
		int i;\
		for(i=sizeof(val)*8-1;i>=0;i--)\
			printf("%d ",(int)(val>>i & 1));\
		printf("\n");\
		}
			

main(){

	short sh=1;
//	pb(sh,sizeof(sh));
//	typeof (sh) k;
//	sh <<= 16;
//	pb(sh,sizeof(sh));

}
