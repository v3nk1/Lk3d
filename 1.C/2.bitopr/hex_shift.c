#include<stdio.h>

main(){

	unsigned short a=0xffff;
	short b=0xffff;
	a >>= 2;
	b >>= 2;//its a singed number so copies 1's of msb while shifting not 0's
	printf("%x\n",a);
	printf("%x\n",b);

}
