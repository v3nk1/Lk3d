#include<stdio.h>

#define SWP_NIB(no) no<<4|no>>4
#define PRNT_BITS(c,SIZE) int i=SIZE *8 -1;for(;i>=0;i--) printf("%d ",c>>i&1);printf("\n");
#define SIZE sizeof(no)

main(){

	unsigned char no=10,c;
	c=SWP_NIB(no);
	PRNT_BITS(c,SIZE)

}
