#include<stdio.h>
#define SWP_BYTE(a) char *p=(char*)&a,*q=(char*)&b,j; \
		    q+=SIZE-1; \
		    for(j=0;j<SIZE;j++) *q--=*p++;
#define PRNT_BITS(b,SIZE) int i=SIZE *8 -1;for(;i>=0;i--) printf("%d ",b>>i&1);printf("\n");
#define SIZE sizeof(a)
main(){
unsigned short int  a=15,b;
SWP_BYTE(a)
PRNT_BITS(b,SIZE)
}
