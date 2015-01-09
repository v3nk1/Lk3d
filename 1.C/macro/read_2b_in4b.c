// read two 2bytes data frm a 4 byte container.

#include<stdio.h>
 
#define PRNT_HEX(a) printf("%x\n%x\n",(unsigned short int)a,a>>16);

main(){

	unsigned int a=0xaabbccdd;
	PRNT_HEX(a)

}
